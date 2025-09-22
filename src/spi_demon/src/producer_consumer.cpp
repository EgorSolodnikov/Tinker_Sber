#include "spi_demon/producer_consumer.hpp"

ProducerConsumer::ProducerConsumer() 
    : rclcpp::Node("producer_consumer")
    , running_flag_(true)
    , data_available_(false) 
{}

ProducerConsumer::~ProducerConsumer() {
    stop();
}

CallbackReturn ProducerConsumer::init() {
    imu_pub_ = this->create_publisher<hardware_msg::msg::ImuState>("/imu_state", rclcpp::QoS(10));
    motors_state_pub_ = this->create_publisher<hardware_msg::msg::MotorsState>("/motors_state", rclcpp::QoS(10));
    motors_telemetry_pub_ = this->create_publisher<hardware_msg::msg::MotorsTelemetry>("/motors_telemetry", rclcpp::QoS(10));

    spi_reader_ = std::make_unique<SpiReader>();

    return CallbackReturn::SUCCESS;
}

CallbackReturn ProducerConsumer::start() {
    producer_thread_ = std::thread([this] { this->producer_loop(); });
    consumer_thread_ = std::thread([this] { this->consumer_loop(); });

    return CallbackReturn::SUCCESS;
}

void ProducerConsumer::producer_loop() {
    auto logger = this->get_logger();

    while (running_flag_.load()) {
        std::unique_lock<std::mutex> lock(mutex_);
        bool res = spi_reader_->read_data();
        if (!res) {
            RCLCPP_ERROR(logger, "cant set data in read_data()");
        } else {
            data_available_ = res;
        }
        producer_cv_.notify_one();
    }
}

void ProducerConsumer::consumer_loop() {
    while (running_flag_.load()) {
        std::unique_lock<std::mutex> lock(mutex_);
        producer_cv_.wait(lock, [this] { return !running_flag_.load() || data_available_; });
        if (!running_flag_.load()) {
            break;
        }
        imu_pub_->publish(spi_reader_->get_imu_data());
        motors_state_pub_->publish(spi_reader_->get_motors_state_data());
        motors_telemetry_pub_->publish(spi_reader_->get_motors_telemetries_data());
        data_available_ = false;
    }
}

CallbackReturn ProducerConsumer::stop() {
    running_flag_.store(false);
    producer_cv_.notify_all();
    consumer_thread_.join();
    producer_thread_.join();
    spi_reader_.reset();
    return CallbackReturn::SUCCESS;
}