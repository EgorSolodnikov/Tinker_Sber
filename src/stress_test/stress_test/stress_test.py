import rclpy
from rclpy.node import Node
import time
import random

from hardware_msg.msg import MotorsCommands, MotorsStates, MotorParameters


class MotorResponseTest(Node):
    def __init__(self):
        super().__init__('motor_response_test')

        self.pub_com = self.create_publisher(MotorsCommands, 'motors/commands', 10)
        self.pub_param = self.create_publisher(MotorParameters, 'motor/params', 10)
        self.sub = self.create_subscription(MotorsStates, 'motors/states', self.state_callback, 10)

        self.test_count = 5
        self.connected_motors = 2
        self.num_motors = 10
        self.tolerance = 3.0
        self.move_threshold = 1.0
        self.timeout = 5.0

        self.current_pos = [0.0] * self.num_motors
        self.initial_pos = [0.0] * self.num_motors
        self.prev_pos = [0.0] * self.num_motors
        self.target_pos = [0.0] * self.num_motors
        self.start_times = [0.0] * self.num_motors
        self.moved = [False] * self.num_motors
        self.response_times = [[] for _ in range(self.num_motors)]
        self.has_states = False
        self.initialized = False
        self.test_started = False

        self.wait_for_initial_data()
        self.run_test()

    def wait_for_initial_data(self):
        """Ждем первые данные от энкодеров, чтобы считать абсолютные позиции"""
        start = time.time()
        while time.time() - start < 10.0:
            rclpy.spin_once(self, timeout_sec=0.1)
            if self.has_states:
                self.initial_pos = self.current_pos[:]
                connected_init = [self.initial_pos[i] for i in range(self.connected_motors)]
                self.get_logger().info(f"Начальные абсолютные позиции: {connected_init}")
                self.initialized = True
                return
        self.get_logger().error("Нет данных энкодеров, завершение.")
        rclpy.shutdown()

    def run_test(self):
        if not self.initialized:
            return

        # Включаем двигатели
        params = MotorParameters()
        params.enable = True
        params.kp = 10.0
        params.kd = 1.0
        self.pub_param.publish(params)
        time.sleep(1.0)

        for test_round in range(self.test_count):
            self.test_started = True
            self.get_logger().info(f"\n Тест #{test_round + 1} из {self.test_count}")

            targets = [ float(random.randint(0, 120)) if i < self.connected_motors else 0.0 for i in range(self.num_motors)]
            #targets = [ 0.0 for i in range(self.num_motors)]

            self.prev_pos = self.current_pos[:]
            self.moved = [False] * self.num_motors
            self.send_targets(targets)

            start = time.time()
            while time.time() - start < self.timeout:
                rclpy.spin_once(self, timeout_sec=0.05)
            time.sleep(1.0)

        #self.print_results()

        # Отключаем двигатели
        params.enable = False
        self.pub_param.publish(params)
        self.get_logger().info("Двигатели выключены")
        rclpy.shutdown()

    def send_targets(self, targets):
        msg = MotorsCommands()
        msg.target_pos = targets
        msg.target_vel = [0.0] * self.num_motors
        msg.target_trq = [0.0] * self.num_motors
        self.pub_com.publish(msg)
        self.target_pos = targets[:]
        self.start_times = [time.time()] * self.num_motors
        connected_targets = [targets[i] for i in range(self.connected_motors)]
        self.get_logger().info(f"Отправлены целевые позиции: {connected_targets}")

    def state_callback(self, msg):
        self.current_pos = msg.current_pos
        self.has_states = True

        if self.test_started:
            for i in range(self.connected_motors):
                if not self.moved[i]:
                    delta = abs(self.current_pos[i] - self.prev_pos[i])
                    if delta >= self.move_threshold:
                        t = time.time() - self.start_times[i]
                        self.response_times[i].append(t)
                        self.moved[i] = True
                        self.get_logger().info(f"Двигатель {i+1} откликнулся через {1000*t:.0f} мс")

    # def print_results(self):
    #     self.get_logger().info("\nРезультаты теста:")
    #     for i in range(self.connected_motors):
    #         if self.response_times[i]:
    #             avg = sum(self.response_times[i]) / len(self.response_times[i])
    #             self.get_logger().info(f"  Двигатель {i+1}: {avg:.3f} сек")
    #         else:
    #             self.get_logger().info(f"  Двигатель {i+1}: нет отклика")


def main():
    rclpy.init()
    node = MotorResponseTest()
    rclpy.spin(node)


if __name__ == '__main__':
    main()
