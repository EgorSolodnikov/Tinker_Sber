#!/usr/bin/env python3
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QSlider, QLabel
from PyQt5.QtCore import Qt
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray

class MotorSliderNode(Node):
    def __init__(self):
        super().__init__('motor_slider_gui')
        self.publisher_ = self.create_publisher(Float32MultiArray, '/motors/commands/motor_1', 10)

    def publish(self, values):
        msg = Float32MultiArray()
        msg.data = values
        self.publisher_.publish(msg)

class SliderWindow(QWidget):
    def __init__(self, ros_node):
        super().__init__()
        self.ros_node = ros_node
        self.setWindowTitle('Motor Command Sliders')
        self.layout = QVBoxLayout()
        self.sliders = []
        self.labels = []
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
        self.setLayout(self.layout)
        self.update_ros()

    def make_on_change(self, idx, label):
        def on_change(value):
            label.setText(f'Параметр {idx+1}: {value}')
            self.update_ros()
        return on_change

    def update_ros(self):
        values = [float(slider.value()) for slider in self.sliders]
        self.ros_node.publish(values)

def main(args=None):
    rclpy.init(args=args)
    ros_node = MotorSliderNode()
    app = QApplication(sys.argv)
    window = SliderWindow(ros_node)
    window.show()
    app.exec_()
    ros_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
