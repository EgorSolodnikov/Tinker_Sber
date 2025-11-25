import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, TargetCommand, ControlCommand

class GaitController(Node):
    def __init__(self):
        super().__init__('gait_controller')

        self.state_subscription = self.create_subscription(
            RobotState,
            '/robot/state',
            10
        )

        self.target_subscription = self.create_subscription(
            TargetCommand,
            '/command/target',
            10
        )

        self.control_publisher = self.create_publisher(
            ControlCommand,
            '/control/command',
            10
        )

        self.rl_model = load_rl_model()


def load_rl_model():
    return