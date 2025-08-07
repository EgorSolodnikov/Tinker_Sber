import sys
import rclpy
from rclpy.node import Node
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QSlider, QLabel
from PyQt5.QtCore import Qt
from tinker_motor_gui.msg import MotorParams

class MotorGuiNode(Node):
    def __init__(self):
        super().__init__('motor_gui_node')
        self.publisher_ = self.create_publisher(MotorParams, '/motors/commands/motor_1', 10)
        self.subscription = self.create_subscription(
            MotorParams,
            '/motors/data/motor_1',
            self.listener_callback,
            10)
        self.param1 = 0.0
        self.param2 = 0.0
        self.param3 = 0.0

    def listener_callback(self, msg):
        self.param1 = msg.param1
        self.param2 = msg.param2
        self.param3 = msg.param3

    def publish_params(self, p1, p2, p3):
        msg = MotorParams()
        msg.param1 = p1
        msg.param2 = p2
        msg.param3 = p3
        self.publisher_.publish(msg)

class MotorGui(QWidget):
    def __init__(self, ros_node):
        super().__init__()
        self.ros_node = ros_node
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle('Motor GUI')
        layout = QVBoxLayout()
        self.sliders = []
        self.labels = []
        for i in range(3):
            slider = QSlider(Qt.Horizontal)
            slider.setMinimum(0)
            slider.setMaximum(100)
            slider.setValue(0)
            slider.valueChanged.connect(self.slider_changed)
            label = QLabel(f'Параметр {i+1}: 0.0')
            self.sliders.append(slider)
            self.labels.append(label)
            layout.addWidget(label)
            layout.addWidget(slider)
        self.setLayout(layout)

    def slider_changed(self):
        values = [s.value()/100.0 for s in self.sliders]
        for i, v in enumerate(values):
            self.labels[i].setText(f'Параметр {i+1}: {v:.2f}')
        self.ros_node.publish_params(*values)

def main(args=None):
    rclpy.init(args=args)
    node = MotorGuiNode()
    app = QApplication(sys.argv)
    gui = MotorGui(node)
    gui.show()
    timer = node.create_timer(0.1, lambda: None)  # keep ROS2 spinning
    def spin():
        rclpy.spin_once(node, timeout_sec=0.01)
    app.aboutToQuit.connect(lambda: node.destroy_node())
    app.aboutToQuit.connect(rclpy.shutdown)
    from PyQt5.QtCore import QTimer
    qt_timer = QTimer()
    qt_timer.timeout.connect(spin)
    qt_timer.start(10)
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
