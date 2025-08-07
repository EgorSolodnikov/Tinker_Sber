#!/usr/bin/env python3
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QSlider, QLabel, QDoubleSpinBox, QHBoxLayout, QPushButton
from PyQt5.QtCore import Qt, QTimer
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray

class MotorSliderNode(Node):
    def __init__(self):
        super().__init__('motor_slider_gui')
        self.publisher_ = self.create_publisher(Float32MultiArray, '/motors/commands/motor_1', 10)
        self.kpkd_publisher_ = self.create_publisher(Float32MultiArray, '/motors/commands/kpkd', 10)
        self.kp = 0.0
        self.kd = 0.0
        self.create_timer(5.0, self.publish_kpkd)

    def publish(self, values):
        msg = Float32MultiArray()
        msg.data = values
        self.publisher_.publish(msg)

    def set_kpkd(self, kp, kd):
        self.kp = kp
        self.kd = kd

    def publish_kpkd(self):
        msg = Float32MultiArray()
        msg.data = [self.kp, self.kd]
        self.kpkd_publisher_.publish(msg)

class SliderWindow(QWidget):
    def __init__(self, ros_node):
        super().__init__()
        self.ros_node = ros_node
        self.setWindowTitle('Motor Command Sliders')
        self.layout = QVBoxLayout()
        self.sliders = []
        self.labels = []
        self.publishing_enabled = True
        for i in range(3):
            label = QLabel(f'Параметр {i+1}: 0')
            slider = QSlider(Qt.Horizontal)
            slider.setMinimum(0)
            slider.setMaximum(100)
            slider.setValue(0)
            slider.valueChanged.connect(self.make_on_change(i, label))
            self.layout.addWidget(label)
            self.layout.addWidget(slider)
            self.sliders.append(slider)
            self.labels.append(label)
        # Добавляем поля для kp и kd
        kp_layout = QHBoxLayout()
        kp_label = QLabel('kp:')
        self.kp_spin = QDoubleSpinBox()
        self.kp_spin.setDecimals(3)
        self.kp_spin.setRange(0.0, 100.0)
        self.kp_spin.setSingleStep(0.1)
        self.kp_spin.valueChanged.connect(self.on_kpkd_change)
        kp_layout.addWidget(kp_label)
        kp_layout.addWidget(self.kp_spin)
        self.layout.addLayout(kp_layout)

        kd_layout = QHBoxLayout()
        kd_label = QLabel('kd:')
        self.kd_spin = QDoubleSpinBox()
        self.kd_spin.setDecimals(3)
        self.kd_spin.setRange(0.0, 100.0)
        self.kd_spin.setSingleStep(0.1)
        self.kd_spin.valueChanged.connect(self.on_kpkd_change)
        kd_layout.addWidget(kd_label)
        kd_layout.addWidget(self.kd_spin)
        self.layout.addLayout(kd_layout)

        # Кнопки Старт и Стоп
        btn_layout = QHBoxLayout()
        self.start_btn = QPushButton('Старт')
        self.stop_btn = QPushButton('Стоп')
        self.start_btn.clicked.connect(self.on_start)
        self.stop_btn.clicked.connect(self.on_stop)
        btn_layout.addWidget(self.start_btn)
        btn_layout.addWidget(self.stop_btn)
        self.layout.addLayout(btn_layout)

        self.setLayout(self.layout)
        self.update_ros()

    def make_on_change(self, idx, label):
        def on_change(value):
            label.setText(f'Параметр {idx+1}: {value}')
            self.update_ros()
        return on_change

    def update_ros(self):
        if self.publishing_enabled:
            values = [float(slider.value()) for slider in self.sliders]
            self.ros_node.publish(values)
            self.ros_node.set_kpkd(self.kp_spin.value(), self.kd_spin.value())

    def on_kpkd_change(self):
        if self.publishing_enabled:
            self.ros_node.set_kpkd(self.kp_spin.value(), self.kd_spin.value())

    def on_start(self):
        self.publishing_enabled = True
        self.update_ros()

    def on_stop(self):
        # Перед отключением публикации отправляем нули
        zero_values = [0.0 for _ in self.sliders]
        self.ros_node.publish(zero_values)
        self.ros_node.set_kpkd(0.0, 0.0)
        msg = Float32MultiArray()
        msg.data = [0.0, 0.0]
        self.ros_node.kpkd_publisher_.publish(msg)
        self.publishing_enabled = False
        for slider in self.sliders:
            slider.setValue(0)
        self.update_ros()

def main(args=None):
    rclpy.init(args=args)
    ros_node = MotorSliderNode()
    app = QApplication(sys.argv)
    window = SliderWindow(ros_node)
    window.show()

    # Интеграция ROS2 event loop в PyQt
    def spin_ros():
        rclpy.spin_once(ros_node, timeout_sec=0)
    ros_timer = QTimer()
    ros_timer.timeout.connect(spin_ros)
    ros_timer.start(10)  # каждые 10 мс

    app.exec_()
    ros_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
