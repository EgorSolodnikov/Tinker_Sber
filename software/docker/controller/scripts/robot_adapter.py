import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, ControlCommand

class RobotAdapter(Node):
    def __init__(self):
        super().__init__('robot_adapter')