from abc import ABC, abstractmethod
import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, ControlCommand, TargetCommand

class BaseAdapter(ABC):
    def __init__(self, node: Node):
        self.node = node
        self.state_subscriber= None
        self.target_subscriber = None
        self.control_publisher = None

    @abstractmethod
    def initialize(self):
        pass

    @abstractmethod
    def subscribe_target(self, target_msg):
        pass

    @abstractmethod
    def publish_control(self, control_msg):
        pass
        
    @abstractmethod
    def shutdown(self):
        pass


class IsaacAdapter(BaseAdapter):
    def __init__(self):
        super().__init__('isaac_adapter')
    
    def initialize(self):
        self.state_subscriber = self.node.create_subscription(

        )
        self.target_subscriber = self.node.create_subscription(

        )
        self.control_publisher = self.node.create_publisher(

        )
        self.node.get_logger().info('Isaac adapter initialized')

    def subscribe_target(self, target_msg):
        # convert from topic message into model input
        pass

    def publish_control(self, control_msg):
        # convert from model output into topic message
        pass


class MujocoAdapter(BaseAdapter):
    def __init__(self):
        super().__init__('mujoco_adapter')


class RobotAdapter(BaseAdapter):
    def __init__(self):
        super().__init__('robot_adapter')