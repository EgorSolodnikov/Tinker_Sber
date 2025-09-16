#include <thread>
#include <atomic>
#include <memory>
#include <queue>
#include <csignal>
#include <functional>
#include <condition_variable>
#include <mutex>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/logger.hpp>
#include <hardware_interface/system_interface.hpp>
#include <hardware_interface/types/hardware_interface_type_values.hpp>

#include "hardware_msg/msg/imu_state.hpp"
#include "hardware_msg/msg/motors_state.hpp"
#include "hardware_msg/msg/motors_telemetry.hpp"

#include "spi_reader.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class ProducerConsumer : public rclcpp::Node {
public:
    ProducerConsumer();
    ~ProducerConsumer();

    CallbackReturn init();
    CallbackReturn start();
    CallbackReturn stop();
    void consumer_loop();
    void producer_loop();

private:
    std::unique_ptr<SpiReader> spi_reader_;

    rclcpp::Publisher<hardware_msg::msg::ImuState>::SharedPtr imu_pub_;
    rclcpp::Publisher<hardware_msg::msg::MotorsState>::SharedPtr motors_state_pub_;
    rclcpp::Publisher<hardware_msg::msg::MotorsTelemetry>::SharedPtr motors_telemetry_pub_;

    std::thread producer_thread_;
    std::thread consumer_thread_;

    std::condition_variable producer_cv_;
    std::condition_variable consumer_cv_;
    std::mutex mutex_;
    std::atomic<bool> running_flag_;
    bool data_available_;
};