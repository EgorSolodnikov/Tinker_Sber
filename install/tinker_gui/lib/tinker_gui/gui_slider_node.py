#!/usr/bin/env python3
import sys
from typing import List, Tuple
from PyQt5.QtWidgets import (
    QApplication,
    QWidget,
    QVBoxLayout,
    QHBoxLayout,
    QGridLayout,
    QSlider,
    QLabel,
    QGroupBox,
    QScrollArea,
)
from PyQt5.QtCore import Qt, QTimer
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import JointState, Imu
from ament_index_python.packages import get_package_share_directory
import os
import xml.etree.ElementTree as ET

MOTOR_COUNT = 10
JOINT_NAMES_10 = [
    'joint_l_yaw',
    'joint_l_roll',
    'joint_l_pitch',
    'joint_l_knee',
    'joint_l_ankle',
    'joint_r_yaw',
    'joint_r_roll',
    'joint_r_pitch',
    'joint_r_knee',
    'joint_r_ankle',
]

# Порядок полей для /motors/commands/motor_N
MOTOR_PARAM_FIELDS = [
    'id', 'enable', 'reset_zero', 'reset_error',
    'acc_calibrate', 'gyro_calibrate', 'mag_calibrate',
    'beep_state', 'kp', 'kd'
]

class MotorSliderNode(Node):
    def __init__(self):
        super().__init__('tinker_rqt')
        # /motors/commands (общий JointState)
        self.commands_publisher = self.create_publisher(JointState, '/motors/commands', 10)
        # /motors/commands/motor_i (индивидуальные настройки каждого мотора)
        self.motor_publishers: List = []
        for i in range(MOTOR_COUNT):
            topic = f'/motors/commands/motor_{i+1}'
            self.motor_publishers.append(
                self.create_publisher(Float32MultiArray, topic, 10)
            )

        # Подписки на состояния моторов (агрегированные и по каждому мотору)
        self.current_pos: List[float] = [0.0] * MOTOR_COUNT
        self.current_vel: List[float] = [0.0] * MOTOR_COUNT
        self.current_trq: List[float] = [0.0] * MOTOR_COUNT
        self.motor_status: List[List[float]] = [[float(i + 1), 0.0, 0.0, 0.0] for i in range(MOTOR_COUNT)]
        self.create_subscription(JointState, '/motors/states', self._states_cb, 10)
        for i in range(MOTOR_COUNT):
            self.create_subscription(
                Float32MultiArray,
                f'/motors/states/motor_{i+1}',
                lambda msg, idx=i: self._motor_state_cb(idx, msg),
                10,
            )

        # Подписка на IMU
        self.imu_ang = [0.0, 0.0, 0.0]
        self.imu_acc = [0.0, 0.0, 0.0]
        self.create_subscription(Imu, '/imu', self._imu_cb, 10)

    def _states_cb(self, msg: JointState) -> None:
        n = min(MOTOR_COUNT, len(msg.position), len(msg.velocity), len(msg.effort))
        for i in range(n):
            self.current_pos[i] = float(msg.position[i])
            self.current_vel[i] = float(msg.velocity[i])
            self.current_trq[i] = float(msg.effort[i])

    def _motor_state_cb(self, idx: int, msg: Float32MultiArray) -> None:
        data = list(msg.data)
        if len(data) >= 4:
            self.motor_status[idx] = [float(data[0]), float(data[1]), float(data[2]), float(data[3])]

    def _imu_cb(self, msg: Imu) -> None:
        self.imu_ang = [
            float(msg.angular_velocity.x),
            float(msg.angular_velocity.y),
            float(msg.angular_velocity.z),
        ]
        self.imu_acc = [
            float(msg.linear_acceleration.x),
            float(msg.linear_acceleration.y),
            float(msg.linear_acceleration.z),
        ]

    def publish_joint_commands(self, pos_list: List[float], vel_list: List[float], trq_list: List[float]):
        msg = JointState()
        msg.position = [float(v) for v in pos_list]
        msg.velocity = [float(v) for v in vel_list]
        msg.effort = [float(v) for v in trq_list]
        self.commands_publisher.publish(msg)

    def publish_motor_params(self, motor_index: int, values_10_floats: List[float]):
        msg = Float32MultiArray()
        msg.data = [float(v) for v in values_10_floats]
        self.motor_publishers[motor_index].publish(msg)

class SliderWindow(QWidget):
    def __init__(self, ros_node: MotorSliderNode):
        super().__init__()
        self.ros_node = ros_node
        self.setWindowTitle('Tinker RQT')
        self.resize(1200, 800)

        # Загружаем лимиты суставов из URDF
        self.pos_limits: List[Tuple[float, float]] = self._load_limits_from_urdf()
        if len(self.pos_limits) != MOTOR_COUNT:
            self.pos_limits = [(-1.57, 1.57) for _ in range(MOTOR_COUNT)]

        # Контейнер со скроллом
        outer_layout = QVBoxLayout()
        scroll = QScrollArea(self)
        scroll.setWidgetResizable(True)
        content = QWidget()
        self.grid = QGridLayout(content)
        self.grid.setHorizontalSpacing(16)
        self.grid.setVerticalSpacing(12)
        scroll.setWidget(content)
        outer_layout.addWidget(scroll)
        self.setLayout(outer_layout)

        # Хранилища UI-элементов по моторам
        self.motor_cmd_sliders: List[List[QSlider]] = []
        self.motor_cmd_data_labels: List[List[QLabel]] = []
        self.motor_param_sliders: List[List[QSlider]] = []
        self.status_labels: List[dict] = []
        self.last_enable_state: List[bool] = [False] * MOTOR_COUNT

        # Блок IMU в первой строке
        imu_group = QGroupBox('IMU')
        imu_layout = QGridLayout(imu_group)
        self.imu_labels = {
            'ang_x': QLabel('ang_x: 0.000'),
            'ang_y': QLabel('ang_y: 0.000'),
            'ang_z': QLabel('ang_z: 0.000'),
            'acc_x': QLabel('acc_x: 0.000'),
            'acc_y': QLabel('acc_y: 0.000'),
            'acc_z': QLabel('acc_z: 0.000'),
        }
        imu_layout.addWidget(self.imu_labels['ang_x'], 0, 0)
        imu_layout.addWidget(self.imu_labels['ang_y'], 0, 1)
        imu_layout.addWidget(self.imu_labels['ang_z'], 0, 2)
        imu_layout.addWidget(self.imu_labels['acc_x'], 1, 0)
        imu_layout.addWidget(self.imu_labels['acc_y'], 1, 1)
        imu_layout.addWidget(self.imu_labels['acc_z'], 1, 2)
        self.grid.addWidget(imu_group, 0, 0, 1, 2)

        # Создаём группы моторов и раскладываем по колонкам, начиная со 2-й строки
        columns = 2
        for motor_idx in range(MOTOR_COUNT):
            group = self._build_motor_group(motor_idx)
            row = (motor_idx // columns) + 1
            col = motor_idx % columns
            self.grid.addWidget(group, row, col)
            self.last_enable_state[motor_idx] = self._get_enable_state(motor_idx)

        # Таймер
        self.display_timer = QTimer(self)
        self.display_timer.timeout.connect(self._on_timer)
        self.display_timer.start(100)

        self._publish_all(force=True)

    def _load_limits_from_urdf(self) -> List[Tuple[float, float]]:
        limits: List[Tuple[float, float]] = []
        try:
            pkg_share = get_package_share_directory('tinker')
            urdf_path = os.path.join(pkg_share, 'urdf', 'tinker_1.urdf.xacro')
            tree = ET.parse(urdf_path)
            root = tree.getroot()
            joints = {j.get('name'): j for j in root.findall('.//joint')}
            for joint_name in JOINT_NAMES_10:
                j = joints.get(joint_name)
                lower, upper = -1.57, 1.57
                if j is not None:
                    lim = j.find('limit')
                    if lim is not None:
                        try:
                            lower_attr = lim.get('lower')
                            upper_attr = lim.get('upper')
                            if lower_attr is not None:
                                lower = float(lower_attr)
                            if upper_attr is not None:
                                upper = float(upper_attr)
                        except Exception:
                            pass
                limits.append((lower, upper))
        except Exception:
            limits = []
        return limits

    def _build_motor_group(self, motor_index: int) -> QGroupBox:
        group = QGroupBox(f'Motor {motor_index + 1}')
        group_layout = QVBoxLayout(group)

        # Блок команд (pos/vel/trq)
        cmd_box = QGroupBox('Commands')
        cmd_grid = QGridLayout(cmd_box)
        cmd_names = ['target_pos', 'target_vel', 'target_trq']
        cmd_sliders: List[QSlider] = []
        cmd_data_labels: List[QLabel] = []
        for i, name in enumerate(cmd_names):
            label = QLabel(f'{name}: 0')
            slider = QSlider(Qt.Horizontal)
            slider.setMinimum(0)
            slider.setMaximum(100)
            slider.setValue(0)
            slider.valueChanged.connect(lambda val, m=motor_index, lbl=label, n=name: self._on_cmd_change(m, lbl, n, val))
            data_lbl = QLabel('state: 0.0')
            data_lbl.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
            cmd_grid.addWidget(label, i, 0)
            cmd_grid.addWidget(slider, i, 1)
            cmd_grid.addWidget(data_lbl, i, 2)
            cmd_sliders.append(slider)
            cmd_data_labels.append(data_lbl)
        self.motor_cmd_sliders.append(cmd_sliders)
        self.motor_cmd_data_labels.append(cmd_data_labels)
        group_layout.addWidget(cmd_box)

        # Блок параметров (10 полей) + статусы
        param_box = QGroupBox('Parameters')
        param_grid = QGridLayout(param_box)
        connect_lbl = QLabel('connect: 0')
        motor_connected_lbl = QLabel('motor_connected: 0')
        ready_lbl = QLabel('ready: 0')
        param_grid.addWidget(connect_lbl, 0, 0)
        param_grid.addWidget(motor_connected_lbl, 0, 1)
        param_grid.addWidget(ready_lbl, 0, 2)
        self.status_labels.append({'connect': connect_lbl, 'motor_connected': motor_connected_lbl, 'ready': ready_lbl})

        param_sliders: List[QSlider] = []
        for idx, field in enumerate(MOTOR_PARAM_FIELDS):
            row = (idx % 5) + 1
            col = (idx // 5) * 2
            label = QLabel(f'{field}: 0')
            slider = QSlider(Qt.Horizontal)
            if field == 'id':
                fixed_id = float(motor_index + 1)
                slider.setMinimum(int(fixed_id))
                slider.setMaximum(int(fixed_id))
                slider.setValue(int(fixed_id))
                slider.setEnabled(False)
                label.setText(f'{field}: {int(fixed_id)}')
            elif field in {'enable', 'reset_zero', 'reset_error', 'acc_calibrate', 'gyro_calibrate', 'mag_calibrate'}:
                slider.setMinimum(0)
                slider.setMaximum(1)
                slider.setValue(0)
                slider.valueChanged.connect(lambda val, m=motor_index, lbl=label, f=field: self._on_param_change(m, lbl, f, val))
            else:
                slider.setMinimum(0)
                slider.setMaximum(100)
                slider.setValue(0)
                slider.valueChanged.connect(lambda val, m=motor_index, lbl=label, f=field: self._on_param_change(m, lbl, f, val))
            param_grid.addWidget(label, row, col)
            param_grid.addWidget(slider, row, col + 1)
            param_sliders.append(slider)
        self.motor_param_sliders.append(param_sliders)
        group_layout.addWidget(param_box)

        return group

    def _get_enable_state(self, motor_index: int) -> bool:
        enable_slider = self.motor_param_sliders[motor_index][1]
        return enable_slider.value() > 0.5

    def _map_slider_to_pos(self, motor_index: int, slider_value: int) -> float:
        lower, upper = self.pos_limits[motor_index]
        return float(lower + (upper - lower) * (slider_value / 100.0))

    def _on_cmd_change(self, motor_index: int, label: QLabel, name: str, value: int):
        if name == 'target_pos':
            pos = self._map_slider_to_pos(motor_index, value)
            label.setText(f'{name}: {pos:.3f}')
        else:
            label.setText(f'{name}: {value}')
        self._publish_all()

    def _on_param_change(self, motor_index: int, label: QLabel, field: str, value: int):
        label.setText(f'{field}: {value}')
        if field == 'enable':
            self._handle_enable_edge(motor_index)
        self._publish_all()

    def _handle_enable_edge(self, motor_index: int):
        current = self._get_enable_state(motor_index)
        if current == self.last_enable_state[motor_index]:
            return
        if not current:
            self._publish_motor_zero_once(motor_index)
            for slider in self.motor_cmd_sliders[motor_index]:
                slider.setValue(0)
            for idx, slider in enumerate(self.motor_param_sliders[motor_index]):
                if MOTOR_PARAM_FIELDS[idx] in {'enable', 'id'}:
                    continue
                slider.setValue(0)
        else:
            self._publish_all(force=True)
        self.last_enable_state[motor_index] = current

    def _publish_motor_zero_once(self, motor_index: int):
        pos_list, vel_list, trq_list = self._collect_joint_arrays()
        pos_list[motor_index] = 0.0
        vel_list[motor_index] = 0.0
        trq_list[motor_index] = 0.0
        self.ros_node.publish_joint_commands(pos_list, vel_list, trq_list)
        zero_params = [0.0] * len(MOTOR_PARAM_FIELDS)
        zero_params[0] = float(motor_index + 1)
        self.ros_node.publish_motor_params(motor_index, zero_params)

    def _collect_joint_arrays(self):
        pos_list = [0.0] * MOTOR_COUNT
        vel_list = [0.0] * MOTOR_COUNT
        trq_list = [0.0] * MOTOR_COUNT
        for m in range(MOTOR_COUNT):
            if not self._get_enable_state(m):
                continue
            cmd_sliders = self.motor_cmd_sliders[m]
            pos_list[m] = self._map_slider_to_pos(m, cmd_sliders[0].value())
            vel_list[m] = float(cmd_sliders[1].value())
            trq_list[m] = float(cmd_sliders[2].value())
        return pos_list, vel_list, trq_list

    def _collect_motor_params(self, motor_index: int) -> List[float]:
        sliders = self.motor_param_sliders[motor_index]
        return [float(s.value()) for s in sliders]

    def _publish_all(self, force: bool = False):
        pos_list, vel_list, trq_list = self._collect_joint_arrays()
        self.ros_node.publish_joint_commands(pos_list, vel_list, trq_list)
        for m in range(MOTOR_COUNT):
            enabled = self._get_enable_state(m)
            if enabled or force:
                params = self._collect_motor_params(m)
                self.ros_node.publish_motor_params(m, params if enabled else [0.0] * len(params))

    def _update_state_labels(self):
        for m in range(MOTOR_COUNT):
            if m < len(self.motor_cmd_data_labels):
                labels = self.motor_cmd_data_labels[m]
                if len(labels) >= 3:
                    labels[0].setText(f'state: {self.ros_node.current_pos[m]:.2f}')
                    labels[1].setText(f'state: {self.ros_node.current_vel[m]:.2f}')
                    labels[2].setText(f'state: {self.ros_node.current_trq[m]:.2f}')
        for m in range(MOTOR_COUNT):
            if m < len(self.status_labels):
                st = self.ros_node.motor_status[m]
                self.status_labels[m]['connect'].setText(f'connect: {int(st[1])}')
                self.status_labels[m]['motor_connected'].setText(f'motor_connected: {int(st[2])}')
                self.status_labels[m]['ready'].setText(f'ready: {int(st[3])}')

    def _on_timer(self):
        self._publish_all()
        self._update_state_labels()


def main(args=None):
    rclpy.init(args=args)
    ros_node = MotorSliderNode()
    app = QApplication(sys.argv)
    window = SliderWindow(ros_node)
    window.show()

    def spin_ros():
        rclpy.spin_once(ros_node, timeout_sec=0)
    ros_timer = QTimer()
    ros_timer.timeout.connect(spin_ros)
    ros_timer.start(10)

    app.exec_()
    ros_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
