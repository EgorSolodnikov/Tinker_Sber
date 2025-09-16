#include <rclcpp/rclcpp.hpp>

#include "spi_demon/producer_consumer.hpp"


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<ProducerConsumer>();

    auto init_ret = node->init();
    if (init_ret != rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS) {
        RCLCPP_ERROR(node->get_logger(), "Failed to initialize ProducerConsumer");
        rclcpp::shutdown();
        return 1;
    }

    auto start_ret = node->start();
    if (start_ret != rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS) {
        RCLCPP_ERROR(node->get_logger(), "Failed to start ProducerConsumer");
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}