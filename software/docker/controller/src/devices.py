from abc import ABC, abstractmethod
import rclpy
from rclpy.node import Node
from controller_msg.msg import TargetCommand
from pynput import keyboard

class BaseDevice(ABC):
    def __init__(self, node: Node):
        self.node = node
        self.target_subscriber = None

    @abstractmethod
    def initialize(self):
        pass
    
    @abstractmethod
    def convert(self):
        pass

    @abstractmethod
    def shutdown(self):
        pass


class KeyboardDevice(BaseDevice):
    def __init__(self, node: Node):
        super().__init__(node)
    
    def initialize(self):
        self.keyboard_listener = keyboard.Listener(on_press=self.on_press, on_release=self.on_release)
        
        self.node.get_logger().info('Keyboard device initialized')

    def on_press():
        pass

    def on_release():
        pass

    def convert(self):
        pass

    def shutdown(self):
        pass


class GamepadDevice(BaseDevice):
    def __init__(self, node: Node):
        super().__init__(node)

    def initialize(self):
        self.target_subscriber = self.create_subscription(
            TargetCommand,
            '/control/target',
            10
        )

        self.node.get_logger().info('Gamepad device initialized')

    def convert(self):
        pass

    def shutdown(self):
        self.node.destroy_subscription(self.target_subscriber)
        self.shutdown()

