#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState

JOINT_NAMES_10 = [
    'joint_l_yaw',
    'joint_l_roll',
    'joint_l_pitch',
    'joint_l_knee',
    'joint_l_ankle',
    'joint_r_yaw',
    'joint_r_roll',
    'joint_r_pitch',
    'joint_r_knee',
    'joint_r_ankle',
]

class StatesToJointStates(Node):
    def __init__(self) -> None:
        super().__init__('states_to_joint_states')
        self._pub = self.create_publisher(JointState, '/joint_states', 10)
        self._sub = self.create_subscription(JointState, '/motors/states', self._on_states, 10)
        self.get_logger().info('Bridge started: /motors/states -> /joint_states (10 joints)')

    def _on_states(self, msg: JointState) -> None:
        js = JointState()
        js.name = JOINT_NAMES_10
        positions = list(msg.position[:10]) if len(msg.position) >= 10 else list(msg.position) + [0.0] * (10 - len(msg.position))
        js.position = [float(v) for v in positions]
        js.header.stamp = self.get_clock().now().to_msg()
        self._pub.publish(js)


def main(args=None):
    rclpy.init(args=args)
    node = StatesToJointStates()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
