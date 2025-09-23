#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from hardware_msg.msg import MotorsCommand
from threading import Thread
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QSlider, QLabel, QVBoxLayout, QWidget
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap

class MotorGuiNode(Node):
    def __init__(self):
        super().__init__('motor_gui_node')
        self.publisher = self.create_publisher(MotorsCommand, 'MotorsCommand', 10)
        self.positions = [50.0] * 10
    def publish_positions(self):
        msg = MotorsCommand()
        msg.position = self.positions
        self.publisher.publish(msg)
        self.get_logger().info(f'Publish position: {self.positions}')

class MotorGUI(QMainWindow):
    def __init__(self, node):
        super().__init__()
        self.node = node
        self.setWindowTitle('Motor Control GUI (10 Motors)')
        self.setGeometry(100, 100, 500, 700)

        self.setStyleSheet("""
            QMainWindow {
                background-color: #2b2b2b;
                color: white;
            }
            QLabel {
                font-weight: bold;
                font-size: 12px;
                color: white;
                padding: 5px;
                border: 1px solid #555;
                background-color: #3c3c3c;
                border-radius: 5px;
            }
            QSlider::groove:horizontal {
                border: 1px solid #999;
                height: 8px;
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4e79a0, stop:1 #f28e2b);
                margin: 2px 0;
                border-radius: 4px;
            }
            QSlider::handle:horizontal {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ffffff, stop:1 #dddddd);
                border: 1px solid #444;
                width: 18px;
                margin: -2px 0;
                border-radius: 9px;
            }
            QWidget {
                background-color: #2b2b2b;
            }
        """)

        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)
        layout.setSpacing(10)
        layout.setContentsMargins(20, 20, 20, 20)

        self.image_label = QLabel()
        pixmap = QPixmap('/motors_command_gui/icons/robot.png')
        if not pixmap.isNull():
            self.image_label.setPixmap(pixmap.scaled(200, 100, Qt.KeepAspectRatio))
        else:
            self.image_label.setText("Image not found")
        self.image_label.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.image_label)

        self.sliders = []
        self.position_labels = []
        for i in range(10):
            # Лейбл мотора
            motor_label = QLabel(f'Motor {i+1} Position:')
            layout.addWidget(motor_label)

            # Слайдер
            slider = QSlider(Qt.Horizontal)
            slider.setMinimum(0)
            slider.setMaximum(100)
            slider.setValue(50)
            slider.valueChanged.connect(lambda value, idx=i: self.on_slider_changed(value, idx))
            layout.addWidget(slider)
            self.sliders.append(slider)

            # Лейбл текущей позиции
            position_label = QLabel(f'Position: 50.0')
            layout.addWidget(position_label)
            self.position_labels.append(position_label)

        # Кнопка "Reset All" (бонус, для удобства)
        from PyQt5.QtWidgets import QPushButton
        reset_button = QPushButton('Reset All to 50')
        reset_button.clicked.connect(self.reset_all)
        reset_button.setStyleSheet("QPushButton { background-color: #4e79a0; color: white; border: none; padding: 10px; font-weight: bold; border-radius: 5px; } QPushButton:hover { background-color: #f28e2b; }")
        layout.addWidget(reset_button)

    def on_slider_changed(self, value, motor_index):
        self.node.positions[motor_index] = float(value)
        self.node.publish_positions()
        # Обновляем лейбл позиции
        self.position_labels[motor_index].setText(f'Position: {value:.1f}')

    def reset_all(self):
        for i in range(10):
            self.sliders[i].setValue(50)
            self.node.positions[i] = 50.0
            self.position_labels[i].setText('Position: 50.0')
        self.node.publish_positions()

def main(args=None):
    rclpy.init(args=args)
    node = MotorGuiNode()
    executor = MultiThreadedExecutor()

    app = QApplication(sys.argv)
    gui = MotorGUI(node)
    gui.show()

    # Запуск ROS в отдельном потоке
    thread = Thread(target=executor.spin)
    thread.start()
    node.get_logger().info('ROS2 нода запущена')

    try:
        sys.exit(app.exec_())
    finally:
        node.get_logger().info('Завершение')
        node.destroy_node()
        executor.shutdown()

if __name__ == '__main__':
    main()