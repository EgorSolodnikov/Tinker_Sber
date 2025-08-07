import rclpy
from rclpy.node import Node
from tinker_motor_gui.msg import MotorParams

class MotorPublisherNode(Node):
    def __init__(self):
        super().__init__('motor_publisher_node')
        self.publisher_ = self.create_publisher(MotorParams, '/motors/data/motor_1', 10)
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = MotorParams()
        msg.param1 = 0.5
        msg.param2 = 0.7
        msg.param3 = 0.9
        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = MotorPublisherNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
