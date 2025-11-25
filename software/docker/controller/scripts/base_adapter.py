from abc import ABC, abstractmethod
import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, ControlCommand

class BaseRobotAdapter(ABC):
    def __init__(self, node: Node):
        self.node = node
        self.control_publisher = None
        self.state_publisher = None

    @abstractmethod
    def initialize(self):
        pass
        
    @abstractmethod
    def publish_control(self, control_msg: ControlCommand):
        pass
        
    @abstractmethod
    def shutdown(self):
        pass