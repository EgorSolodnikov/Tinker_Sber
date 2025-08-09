#!/usr/bin/env python3
import math
import random
from typing import List

import rclpy
from rclpy.node import Node

from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import JointState, Imu

MOTOR_COUNT = 5

class FakeStatesPublisher(Node):
    def __init__(self) -> None:
        super().__init__('fake_states_publisher')

        # Aggregate states for all motors
        self.states_pub = self.create_publisher(JointState, '/motors/states', 10)

        # Per-motor state publishers
        self.motor_state_pubs = [
            self.create_publisher(Float32MultiArray, f'/motors/states/motor_{i+1}', 10)
            for i in range(MOTOR_COUNT)
        ]

        # IMU publisher
        self.imu_pub = self.create_publisher(Imu, '/imu', 10)

        # Timers
        self.create_timer(0.10, self.publish_aggregate_states)   # 10 Hz
        self.create_timer(0.20, self.publish_per_motor_states)   # 5 Hz
        self.create_timer(0.05, self.publish_imu)                # 20 Hz

        self.t = 0.0

    def publish_aggregate_states(self) -> None:
        # Generate smooth pseudo data using sin/cos
        self.t += 0.1
        pos = [10.0 * math.sin(self.t + i) for i in range(MOTOR_COUNT)]
        vel = [5.0 * math.cos(self.t * 0.8 + i * 0.3) for i in range(MOTOR_COUNT)]
        trq = [50.0 * math.sin(self.t * 0.5 + i * 0.6) for i in range(MOTOR_COUNT)]

        msg = JointState()
        msg.position = [float(v) for v in pos]
        msg.velocity = [float(v) for v in vel]
        msg.effort = [float(v) for v in trq]
        self.states_pub.publish(msg)

    def publish_per_motor_states(self) -> None:
        # For each motor publish [id, connect, motor_connected, ready]
        for i in range(MOTOR_COUNT):
            motor_id = float(i + 1)
            # Flip with some probability to simulate changes
            connect = float(random.choice([0, 1]))
            motor_connected = float(random.choice([0, 1]))
            ready = float(random.choice([0, 1]))
            msg = Float32MultiArray()
            msg.data = [motor_id, connect, motor_connected, ready]
            self.motor_state_pubs[i].publish(msg)

    def publish_imu(self) -> None:
        # Simple synthetic IMU data
        t = self.t
        imu = Imu()
        # Orientation (no valid orientation -> keep zeros, covariance -1 to indicate unknown)
        imu.orientation_covariance[0] = -1.0
        # Angular velocity (rad/s)
        imu.angular_velocity.x = 0.1 * math.sin(0.7 * t)
        imu.angular_velocity.y = 0.1 * math.cos(0.5 * t)
        imu.angular_velocity.z = 0.1 * math.sin(0.9 * t)
        # Linear acceleration (m/s^2)
        imu.linear_acceleration.x = 0.5 * math.sin(0.4 * t)
        imu.linear_acceleration.y = 0.5 * math.cos(0.6 * t)
        imu.linear_acceleration.z = 9.81 + 0.2 * math.sin(0.8 * t)
        self.imu_pub.publish(imu)


def main(args=None):
    rclpy.init(args=args)
    node = FakeStatesPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
