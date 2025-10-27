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
    QSpinBox,
    QDoubleSpinBox,
    QCheckBox,
    QPushButton,
)
from PyQt5.QtCore import Qt, QTimer
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import JointState
from geometry_msgs.msg import Vector3
from std_msgs.msg import UInt8MultiArray, Float32
from ament_index_python.packages import get_package_share_directory
import os
import xml.etree.ElementTree as ET

MOTOR_COUNT = 12
JOINT_NAMES_10 = [
    "joint_l_yaw",
    "joint_l_roll",
    "joint_l_pitch",
    "joint_l_knee",
    "joint_l_ankle",
    "joint_r_yaw",
    "joint_r_roll",
    "joint_r_pitch",
    "joint_r_knee",
    "joint_r_ankle",
]

# Порядок полей для /motors/commands/motor_N
MOTOR_PARAM_FIELDS = ["id", "enable", "reset_zero", "reset_error", "kp", "kd"]


class MotorSliderNode(Node):
    def __init__(self):
        super().__init__("tinker_rqt")
        # /motors/commands (общий JointState)
        self.commands_publisher = self.create_publisher(
            JointState, "/motors/commands", 10
        )
        # /motors/commands/motor_i (индивидуальные настройки каждого мотора)
        self.motor_publishers: List = []
        for i in range(MOTOR_COUNT):
            topic = f"/motors/commands/motor_{i+1}"
            self.motor_publishers.append(
                self.create_publisher(Float32MultiArray, topic, 10)
            )

        # Подписки на состояния моторов (агрегированные и по каждому мотору)
        self.current_pos: List[float] = [0.0] * MOTOR_COUNT
        self.current_vel: List[float] = [0.0] * MOTOR_COUNT
        self.current_trq: List[float] = [0.0] * MOTOR_COUNT
        self.motor_status: List[List[float]] = [
            [float(i + 1), 0.0, 0.0, 0.0] for i in range(MOTOR_COUNT)
        ]
        self.create_subscription(JointState, "/motors/states", self._states_cb, 10)
        for i in range(MOTOR_COUNT):
            self.create_subscription(
                Float32MultiArray,
                f"/motors/states/motor_{i+1}",
                lambda msg, idx=i: self._motor_state_cb(idx, msg),
                10,
            )

        # Подписка на IMU data (pitch, roll, yaw)
        self.imu_pry = [0.0, 0.0, 0.0]
        self.create_subscription(Vector3, "/imu/data", self._imu_cb, 10)

        # Паблишеры IMU и Control Board команд
        self.imu_cmd_pub = self.create_publisher(UInt8MultiArray, "/imu/commands", 10)
        self.cb_cmd_pub = self.create_publisher(Float32, "/control_board/commands", 10)

    def _states_cb(self, msg: JointState) -> None:
        n = min(MOTOR_COUNT, len(msg.position), len(msg.velocity), len(msg.effort))
        for i in range(n):
            self.current_pos[i] = float(msg.position[i])
            self.current_vel[i] = float(msg.velocity[i])
            self.current_trq[i] = float(msg.effort[i])

    def _motor_state_cb(self, idx: int, msg: Float32MultiArray) -> None:
        data = list(msg.data)
        if len(data) >= 4:
            self.motor_status[idx] = [
                float(data[0]),
                float(data[1]),
                float(data[2]),
                float(data[3]),
            ]

    def _imu_cb(self, msg: Vector3) -> None:
        self.imu_pry = [float(msg.x), float(msg.y), float(msg.z)]

    def publish_joint_commands(
        self, pos_list: List[float], vel_list: List[float], trq_list: List[float]
    ):
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
        self.setWindowTitle("Tinker RQT")
        self.resize(1200, 800)

        # Загружаем лимиты суставов из URDF
        self.pos_limits: List[Tuple[float, float]] = self._load_limits_from_urdf()
        if len(self.pos_limits) != MOTOR_COUNT:
            self.pos_limits = [(-1.57, 1.57) for _ in range(MOTOR_COUNT)]

        # Контейнер со скроллом
        outer_layout = QVBoxLayout()
        
        # Красная кнопка СТОП в верхней части
        stop_button = QPushButton("СТОП")
        stop_button.setStyleSheet("QPushButton { background-color: red; color: white; font-weight: bold; font-size: 16px; padding: 10px; }")
        stop_button.clicked.connect(self._emergency_stop)
        outer_layout.addWidget(stop_button)
        
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
        self.motor_cmd_spinboxes: List[List[QDoubleSpinBox]] = []
        self.motor_cmd_data_labels: List[List[QLabel]] = []
        self.motor_param_spinboxes: List[List[QDoubleSpinBox]] = []
        self.motor_param_checkboxes: List[List[QCheckBox]] = []
        self.last_enable_state: List[bool] = [False] * MOTOR_COUNT
        # Отдельные элементы UI для IMU команд и beep_state
        self.chk_acc_cal = QCheckBox("acc_calibrate")
        self.chk_mag_cal = QCheckBox("mag_calibrate")
        self.chk_gyro_cal = QCheckBox("gyro_calibrate")
        self.beep_state_spin = QDoubleSpinBox()
        self.beep_state_spin.setRange(0.0, 1000.0)
        self.beep_state_spin.setDecimals(3)

        # Блок IMU в первой строке
        imu_group = QGroupBox("IMU")
        imu_layout = QGridLayout(imu_group)
        self.imu_labels = {
            "pitch": QLabel("pitch: 0.000"),
            "roll": QLabel("roll: 0.000"),
            "yaw": QLabel("yaw: 0.000"),
        }
        imu_layout.addWidget(self.imu_labels["pitch"], 0, 0)
        imu_layout.addWidget(self.imu_labels["roll"], 0, 1)
        imu_layout.addWidget(self.imu_labels["yaw"], 0, 2)
        # Команды IMU (калибровки)
        imu_layout.addWidget(self.chk_acc_cal, 1, 0)
        imu_layout.addWidget(self.chk_mag_cal, 1, 1)
        imu_layout.addWidget(self.chk_gyro_cal, 1, 2)
        self.grid.addWidget(imu_group, 0, 0)

        # Блок Control Board (справа от IMU)
        cb_group = QGroupBox("Control Board")
        cb_layout = QGridLayout(cb_group)
        cb_layout.addWidget(QLabel("beep_state"), 0, 0)
        cb_layout.addWidget(self.beep_state_spin, 0, 1)
        self.grid.addWidget(cb_group, 0, 1)

        # Создаём группы моторов и раскладываем по колонкам, начиная со 2-й строки
        columns = 2
        for motor_idx in range(MOTOR_COUNT):
            group = self._build_motor_group(motor_idx)
            row = (motor_idx // columns) + 1
            col = motor_idx % columns
            self.grid.addWidget(group, row, col)
            self.last_enable_state[motor_idx] = False

        # Таймер
        self.display_timer = QTimer(self)
        self.display_timer.timeout.connect(self._on_timer)
        self.display_timer.start(100)

        # Не публикуем автоматически
        self._publish_all()

    def _load_limits_from_urdf(self) -> List[Tuple[float, float]]:
        limits: List[Tuple[float, float]] = []
        try:
            pkg_share = get_package_share_directory("tinker")
            urdf_path = os.path.join(pkg_share, "urdf", "tinker_1.urdf.xacro")
            tree = ET.parse(urdf_path)
            root = tree.getroot()
            joints = {j.get("name"): j for j in root.findall(".//joint")}
            for joint_name in JOINT_NAMES_10:
                j = joints.get(joint_name)
                lower, upper = -1.57, 1.57
                if j is not None:
                    lim = j.find("limit")
                    if lim is not None:
                        try:
                            lower_attr = lim.get("lower")
                            upper_attr = lim.get("upper")
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
        group = QGroupBox(f"Motor {motor_index + 1}")
        group_layout = QVBoxLayout(group)

        # Блок команд (pos/vel/trq)
        cmd_box = QGroupBox("Commands")
        cmd_grid = QGridLayout(cmd_box)
        cmd_names = ["target_pos", "target_vel", "target_trq"]
        cmd_spinboxes: List[QDoubleSpinBox] = []
        cmd_data_labels: List[QLabel] = []
        for i, name in enumerate(cmd_names):
            label = QLabel(f"{name}: 0")
            spinbox = QDoubleSpinBox()
            if name == "target_pos":
                # Для target_pos используем пределы из URDF
                lower, upper = self.pos_limits[motor_index]
                spinbox.setMinimum(lower)
                spinbox.setMaximum(upper)
                spinbox.setValue(0.0)
                spinbox.setDecimals(3)
            else:
                # Для velocity и torque используем разумные пределы
                spinbox.setMinimum(-100.0)
                spinbox.setMaximum(100.0)
                spinbox.setValue(0.0)
                spinbox.setDecimals(3)
            spinbox.valueChanged.connect(
                lambda val, m=motor_index, lbl=label, n=name: self._on_cmd_change(
                    m, lbl, n, val
                )
            )
            data_lbl = QLabel("state: 0.0")
            data_lbl.setAlignment(Qt.AlignRight | Qt.AlignVCenter)
            cmd_grid.addWidget(label, i, 0)
            cmd_grid.addWidget(spinbox, i, 1)
            cmd_grid.addWidget(data_lbl, i, 2)
            cmd_spinboxes.append(spinbox)
            cmd_data_labels.append(data_lbl)
        self.motor_cmd_spinboxes.append(cmd_spinboxes)
        self.motor_cmd_data_labels.append(cmd_data_labels)
        # Кнопка SEND для публикации JointState один раз
        send_btn = QPushButton("SEND")
        send_btn.clicked.connect(
            lambda _, m=motor_index: self._send_cmd_clicked_for_motor(m)
        )
        cmd_grid.addWidget(send_btn, len(cmd_names), 0, 1, 3)
        group_layout.addWidget(cmd_box)

        # Блок параметров
        param_box = QGroupBox("Parameters")
        param_grid = QGridLayout(param_box)

        param_spinboxes: List[QDoubleSpinBox] = []
        param_checkboxes: List[QCheckBox] = []
        for idx, field in enumerate(MOTOR_PARAM_FIELDS):
            row = idx
            col = 0
            label = QLabel(f"{field}:")

            if field == "id":
                # ID - неизменяемое поле
                spinbox = QDoubleSpinBox()
                fixed_id = float(motor_index + 1)
                spinbox.setMinimum(int(fixed_id))
                spinbox.setMaximum(int(fixed_id))
                spinbox.setValue(int(fixed_id))
                spinbox.setEnabled(False)
                label.setText(f"{field}: {int(fixed_id)}")
                param_grid.addWidget(label, row, col)
                param_grid.addWidget(spinbox, row, col + 1)
                param_spinboxes.append(spinbox)
                param_checkboxes.append(QCheckBox())  # Пустая галочка для ID
            elif field == "reset_zero":
                # reset_zero - скрытое поле, управляется кнопкой
                param_spinboxes.append(QDoubleSpinBox())  # Пустой spinbox
                param_checkboxes.append(QCheckBox())  # Пустая галочка
            elif field in {"enable", "reset_error"}:
                # Булевые поля - используем галочки
                checkbox = QCheckBox(field)
                checkbox.setChecked(False)
                if field == "enable":
                    checkbox.stateChanged.connect(
                        lambda state, m=motor_index: self._on_enable_checkbox_change(
                            m, state
                        )
                    )
                param_grid.addWidget(checkbox, row, col, 1, 2)  # Занимаем 2 колонки
                param_spinboxes.append(
                    QDoubleSpinBox()
                )  # Пустой spinbox для булевых полей
                param_checkboxes.append(checkbox)
            else:
                # Числовые поля - используем spinbox
                spinbox = QDoubleSpinBox()
                if field in {"kp", "kd"}:
                    spinbox.setMinimum(0.0)
                    spinbox.setMaximum(1000.0)
                    spinbox.setDecimals(3)
                else:
                    spinbox.setMinimum(0.0)
                    spinbox.setMaximum(100.0)
                    spinbox.setDecimals(3)
                spinbox.setValue(0.0)
                spinbox.valueChanged.connect(
                    lambda val, m=motor_index, lbl=label, f=field: self._on_param_change(
                        m, lbl, f, val
                    )
                )
                param_grid.addWidget(label, row, col)
                param_grid.addWidget(spinbox, row, col + 1)
                param_spinboxes.append(spinbox)
                param_checkboxes.append(
                    QCheckBox()
                )  # Пустая галочка для числовых полей
        self.motor_param_spinboxes.append(param_spinboxes)
        self.motor_param_checkboxes.append(param_checkboxes)
        
        # Кнопка RESET ZERO отдельно
        reset_zero_btn = QPushButton("RESET ZERO")
        reset_zero_btn.clicked.connect(lambda _, m=motor_index: self._reset_zero_clicked(m))
        param_grid.addWidget(reset_zero_btn, len(MOTOR_PARAM_FIELDS), 0, 1, 2)
        
        group_layout.addWidget(param_box)

        return group

    def _get_enable_state(self, motor_index: int) -> bool:
        # enable находится на индексе 1 в MOTOR_PARAM_FIELDS (после удаления reset_zero)
        # MOTOR_PARAM_FIELDS = ["id", "enable", "reset_error", "kp", "kd"]
        return self.motor_param_checkboxes[motor_index][1].isChecked()

    def _map_slider_to_pos(self, motor_index: int, value: float) -> float:
        # Теперь value уже является реальным значением, просто проверяем пределы
        lower, upper = self.pos_limits[motor_index]
        return max(lower, min(upper, value))

    def _on_cmd_change(self, motor_index: int, label: QLabel, name: str, value: float):
        if name == "target_pos":
            pos = self._map_slider_to_pos(motor_index, value)
            label.setText(f"{name}: {pos:.3f}")
        else:
            label.setText(f"{name}: {value:.3f}")
        # Не публикуем автоматически, публикация по кнопке SEND

    def _on_param_change(
        self, motor_index: int, label: QLabel, field: str, value: float
    ):
        label.setText(f"{field}: {value:.3f}")
        if field == "enable":
            self._handle_enable_edge(motor_index)
        # Не публикуем автоматически

    def _on_enable_checkbox_change(self, motor_index: int, state: int):
        # Обрабатываем изменение галочки enable
        self._handle_enable_edge(motor_index)

    def _handle_enable_edge(self, motor_index: int):
        current = self._get_enable_state(motor_index)
        if current == self.last_enable_state[motor_index]:
            return
        if not current:
            # Не публикуем в /motors/commands при выключении
            self._publish_motor_zero_once(motor_index)
            for spinbox in self.motor_cmd_spinboxes[motor_index]:
                spinbox.setValue(0.0)
            for idx, spinbox in enumerate(self.motor_param_spinboxes[motor_index]):
                if MOTOR_PARAM_FIELDS[idx] in {"enable", "id"}:
                    continue
                spinbox.setValue(0.0)
            for idx, checkbox in enumerate(self.motor_param_checkboxes[motor_index]):
                if MOTOR_PARAM_FIELDS[idx] in {"enable", "id"}:
                    continue
                checkbox.setChecked(False)
        else:
            # При включении опубликовать только параметры этого мотора один раз
            params = self._collect_motor_params(motor_index)
            self.ros_node.publish_motor_params(motor_index, params)
        self.last_enable_state[motor_index] = current

    def _publish_motor_zero_once(self, motor_index: int):
        # Не публиковать в /motors/commands при выключении
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
            cmd_spinboxes = self.motor_cmd_spinboxes[m]
            pos_list[m] = self._map_slider_to_pos(m, cmd_spinboxes[0].value())
            vel_list[m] = float(cmd_spinboxes[1].value())
            trq_list[m] = float(cmd_spinboxes[2].value())
        return pos_list, vel_list, trq_list

    def _collect_motor_params(self, motor_index: int) -> List[float]:
        spinboxes = self.motor_param_spinboxes[motor_index]
        checkboxes = self.motor_param_checkboxes[motor_index]
        result = []

        for i, field in enumerate(MOTOR_PARAM_FIELDS):
            if field == "reset_zero":
                # reset_zero всегда 0 в обычном сборе, устанавливается в 1 только кнопкой
                result.append(0.0)
            elif field in {"enable", "reset_error"}:
                # Для булевых полей используем галочки
                result.append(1.0 if checkboxes[i].isChecked() else 0.0)
            else:
                # Для числовых полей используем spinbox
                result.append(float(spinboxes[i].value()))

        return result

    def _publish_all(self, force: bool = False):
        # Публиковать по требованию (SEND) или при включении мотора, не по таймеру
        for m in range(MOTOR_COUNT):
            enabled = self._get_enable_state(m)
            if enabled or force:
                params = self._collect_motor_params(m)
                self.ros_node.publish_motor_params(
                    m, params if enabled else [0.0] * len(params)
                )

    def _update_state_labels(self):
        for m in range(MOTOR_COUNT):
            if m < len(self.motor_cmd_data_labels):
                labels = self.motor_cmd_data_labels[m]
                if len(labels) >= 3:
                    labels[0].setText(f"state: {self.ros_node.current_pos[m]:.2f}")
                    labels[1].setText(f"state: {self.ros_node.current_vel[m]:.2f}")
                    labels[2].setText(f"state: {self.ros_node.current_trq[m]:.2f}")
        # Обновить IMU PRY
        self.imu_labels["pitch"].setText(f"pitch: {self.ros_node.imu_pry[0]:.3f}")
        self.imu_labels["roll"].setText(f"roll: {self.ros_node.imu_pry[1]:.3f}")
        self.imu_labels["yaw"].setText(f"yaw: {self.ros_node.imu_pry[2]:.3f}")

    def _on_timer(self):
        # Не публикуем /motors/commands по таймеру
        self._update_state_labels()

        # Публикация IMU/Control Board команд по таймеру
        self._publish_aux_commands()

    def _publish_aux_commands(self):
        # /imu/commands: три числа 0/1: [acc, mag, gyro]
        imu_msg = UInt8MultiArray()
        acc = 1 if self.chk_acc_cal.isChecked() else 0
        mag = 1 if self.chk_mag_cal.isChecked() else 0
        gyro = 1 if self.chk_gyro_cal.isChecked() else 0
        imu_msg.data = [acc, mag, gyro]
        self.ros_node.imu_cmd_pub.publish(imu_msg)
        # /control_board/commands: одиночный float
        cb_msg = Float32()
        cb_msg.data = float(self.beep_state_spin.value())
        self.ros_node.cb_cmd_pub.publish(cb_msg)

    def _send_cmd_clicked_for_motor(self, motor_index: int):
        # Публикуем один JointState при нажатии SEND (один раз)
        pos_list, vel_list, trq_list = self._collect_joint_arrays()
        self.ros_node.publish_joint_commands(pos_list, vel_list, trq_list)

    def _emergency_stop(self):
        # Отправить команды остановки во все топики моторов и обновить UI
        for motor_index in range(MOTOR_COUNT):
            stop_params = [0.0] * len(MOTOR_PARAM_FIELDS)
            stop_params[0] = float(motor_index + 1)  # id остается
            # enable=0, reset_zero=0, reset_error=0, kp=0, kd=0
            self.ros_node.publish_motor_params(motor_index, stop_params)
            
            # Обновить UI для этого мотора
            checkboxes = self.motor_param_checkboxes[motor_index]
            spinboxes = self.motor_param_spinboxes[motor_index]
            
            for idx, field in enumerate(MOTOR_PARAM_FIELDS):
                if field == "enable":
                    checkboxes[idx].setChecked(False)
                elif field == "reset_error":
                    checkboxes[idx].setChecked(False)
                elif field in {"kp", "kd"}:
                    spinboxes[idx].setValue(0.0)

    def _reset_zero_clicked(self, motor_index: int):
        # Собрать текущие параметры мотора
        current_params = self._collect_motor_params(motor_index)
        
        # Установить reset_zero=1 в текущих параметрах
        # MOTOR_PARAM_FIELDS = ["id", "enable", "reset_zero", "reset_error", "kp", "kd"]
        reset_params = current_params.copy()
        reset_params[2] = 1.0  # reset_zero на индексе 2
        
        # Отправить сообщение
        self.ros_node.publish_motor_params(motor_index, reset_params)


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


if __name__ == "__main__":
    main()
