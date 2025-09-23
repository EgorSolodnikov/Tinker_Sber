import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from hardware_msg.msg import MotorsCommand
from threading import Thread
import sys
import os
from PyQt5.QtWidgets import (QApplication, QWidget, QVBoxLayout, QHBoxLayout, 
                             QGridLayout, QLabel, QSlider, QLineEdit, 
                             QPlainTextEdit, QPushButton)
from PyQt5.QtGui import QPixmap, QColor, QIcon
from PyQt5.QtCore import Qt
from ament_index_python.packages import get_package_share_directory
from functools import partial

class MotorGuiNode(Node):
    def __init__(self):
        super().__init__('motor_gui_node')
        self.publisher = self.create_publisher(MotorsCommand, 'MotorsCommand', 10)
        self.positions = [-50.0, -10.0, -50.0, -10.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0] 

    def publish_positions(self):
        msg = MotorsCommand()
        msg.position = self.positions
        self.publisher.publish(msg)
        self.get_logger().info(f'Publish position: {self.positions}')

class MotorGUI(QWidget):
    def __init__(self, node):
        super().__init__()
        self.node = node
        self.setWindowTitle("Motor Calibration")
        self.setStyleSheet("background-color: #4CAF50;")
        
        main_layout = QVBoxLayout()
        
        title = QLabel("Motor calibration")
        title.setStyleSheet("color: purple; font-size: 20px;")
        title.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(title)
        
        grid_layout = QGridLayout()
        grid_layout.setHorizontalSpacing(100)
        grid_layout.setVerticalSpacing(50)
        self.sliders = []
        self.line_edits = []
        
        slider_stylesheet = """
        QSlider::groove:horizontal {
            background: white;
            height: 20px;
            border-radius: 10px;
        }
        QSlider::handle:horizontal {
            background: #e57373;
            width: 30px;
            height: 30px;
            margin: -5px 0;
            border-radius: 15px;
        }
        """
        
        for i in range(10):
            motor_vbox = QVBoxLayout()
            
            motor_label = QLabel(f"{i+1} Motor")
            motor_label.setStyleSheet("color: darkred;")
            motor_label.setAlignment(Qt.AlignCenter)
            motor_vbox.addWidget(motor_label)
            
            slider = QSlider(Qt.Horizontal)
            slider.setStyleSheet(slider_stylesheet)
            slider.setMinimum(-1092)
            slider.setMaximum(1092)
            slider.setValue(int(self.node.positions[i]))
            slider.setMinimumWidth(300)
            slider.valueChanged.connect(lambda value, idx=i: self.update_position(idx, value))
            self.sliders.append(slider)
            motor_vbox.addWidget(slider)
            
            pos_hbox = QHBoxLayout()
            pos_label = QLabel("Position:")
            pos_hbox.addWidget(pos_label)
            
            line_edit = QLineEdit(str(self.node.positions[i]))
            line_edit.setFixedWidth(50)
            line_edit.returnPressed.connect(partial(self.update_from_edit, i))
            self.line_edits.append(line_edit)
            pos_hbox.addWidget(line_edit)
            
            motor_vbox.addLayout(pos_hbox)
            
            row = i // 2
            col = i % 2
            grid_layout.addLayout(motor_vbox, row, col)
        
        main_layout.addLayout(grid_layout)
        
        send_button = QPushButton("Send Positions")
        send_button.clicked.connect(self.send_positions)
        main_layout.addWidget(send_button)
        
        self.log_text = QPlainTextEdit()
        self.log_text.setReadOnly(True)
        main_layout.addWidget(self.log_text)
        
        self.setLayout(main_layout)
    
    def update_position(self, index, value):
        self.node.positions[index] = float(value)
        self.line_edits[index].setText(str(value))
    
    def update_from_edit(self, index):
        text = self.line_edits[index].text()
        try:
            value = float(text)
            if -1092 <= value <= 1092:
                self.node.positions[index] = value
                self.sliders[index].setValue(int(value))
            else:
                self.line_edits[index].setText(str(self.node.positions[index]))
                error_msg = f'Invalid position for motor {index+1}: {value} (out of range -1092 to 1092)'
                self.log_text.appendPlainText(error_msg)
                self.node.get_logger().warning(error_msg)
        except ValueError:
            self.line_edits[index].setText(str(self.node.positions[index]))
            error_msg = f'Invalid input for motor {index+1}: {text} (not a number)'
            self.log_text.appendPlainText(error_msg)
            self.node.get_logger().warning(error_msg)
    
    def send_positions(self):
        self.node.publish_positions()
        self.log_text.appendPlainText(f'Publish position: {self.node.positions}')

def main(args=None):
    rclpy.init(args=args)
    motor_gui_node = MotorGuiNode()
    app = QApplication(sys.argv)
    gui = MotorGUI(motor_gui_node)
    gui.show()
    
    executor = MultiThreadedExecutor()
    executor.add_node(motor_gui_node)
    executor_thread = Thread(target=executor.spin, daemon=True)
    executor_thread.start()
    
    try:
        app.exec_()
    except SystemExit:
        pass
    finally:
        executor.shutdown()
        motor_gui_node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()