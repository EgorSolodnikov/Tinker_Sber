import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, ControlCommand

class MujocoAdapter(Node):
    def __init__(self):
        super().__init__('mujoco_adapter')