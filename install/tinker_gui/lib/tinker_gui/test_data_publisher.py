#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
import random

class TestDataPublisher(Node):
    def __init__(self):
        super().__init__('test_data_publisher')
        self.motor_pub = self.create_publisher(Float32MultiArray, '/motors/data/motor_1', 10)
        self.kpkd_pub = self.create_publisher(Float32MultiArray, '/motors/data/kpkd', 10)
        self.create_timer(5.0, self.publish_data)

    def publish_data(self):
        motor_msg = Float32MultiArray()
        motor_msg.data = [random.uniform(0, 100) for _ in range(3)]
        self.motor_pub.publish(motor_msg)
        kpkd_msg = Float32MultiArray()
        kpkd_msg.data = [random.uniform(0, 10), random.uniform(0, 10)]
        self.kpkd_pub.publish(kpkd_msg)

def main(args=None):
    rclpy.init(args=args)
    node = TestDataPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
