from abc import ABC, abstractmethod
import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, ControlCommand, TargetCommand

class BaseAdapter(ABC):
    def __init__(self, node: Node):
        self.node = node
        self.state_subscriber= None
        self.control_publisher = None

    @abstractmethod
    def initialize(self):
        pass

    @abstractmethod
    def publish_control(self, control_msg):
        pass
        
    @abstractmethod
    def shutdown(self):
        self.node.destroy_subscription(self.state_subscriber)
        self.node.destroy_publisher(self.control_publisher)


class IsaacAdapter(BaseAdapter):
    def __init__(self, node: Node):
        super().__init__(node)
    
    def initialize(self):
        self.state_subscriber = self.node.create_subscription(
            #
        )
        self.control_publisher = self.node.create_publisher(
            #
        )
        self.node.get_logger().info('Isaac adapter initialized')

    def publish_control(self, action):
        # convert from model output (action) into topic message
        pass

    def shutdown(self):
        return super().shutdown()


class MujocoAdapter(BaseAdapter):
    def __init__(self, node: Node):
        super().__init__(node)


class RobotAdapter(BaseAdapter):
    def __init__(self, node: Node):
        super().__init__(node)