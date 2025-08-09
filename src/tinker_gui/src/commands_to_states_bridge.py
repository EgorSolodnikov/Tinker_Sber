#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState


class CommandsToStatesBridge(Node):
    def __init__(self) -> None:
        super().__init__('commands_to_states_bridge')
        self._pub = self.create_publisher(JointState, '/motors/states', 10)
        self._sub = self.create_subscription(JointState, '/motors/commands', self._on_cmd, 10)
        self.get_logger().info('Bridge started: /motors/commands -> /motors/states (JointState passthrough)')

    def _on_cmd(self, msg: JointState) -> None:
        self._pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = CommandsToStatesBridge()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
