#ifndef SPI_READER_HPP 
#define SPI_READER_HPP

#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>
#include <vector>
#include <stdexcept>

#include "hardware_msg/msg/imu_state.hpp"
#include "hardware_msg/msg/motors_state.hpp"
#include "hardware_msg/msg/motors_telemetry.hpp"

#include "circular_buffer_spi.hpp"

class SpiReader{

private:
    //Parameters for reading/writing SPI
    int spi_fd_;
    std::string device_;
    uint32_t speed_;
    uint8_t mode_;
    uint8_t bits_per_word_;
    size_t transfer_size_;

    //Buffers for read/write
    std::vector<uint8_t> tx_buffer_;
    std::vector<uint8_t> rx_buffer_;

    //Buffer for saving data
    circular_buffer<hardware_msg::msg::ImuState> imu_buffer_;
    circular_buffer<hardware_msg::msg::MotorsState> motors_state_buffer_;
    circular_buffer<hardware_msg::msg::MotorsTelemetry> motors_telemetry_buffer_;

    hardware_msg::msg::ImuState internal_parse_imu_data() const; 
    hardware_msg::msg::MotorsState internal_parse_motor_state_data() const;
    hardware_msg::msg::MotorsTelemetry internal_parse_motor_telemetry_data() const;

public:

    SpiReader(const std::string& device = "/dev/spidev0.0", 
              uint32_t speed = 1000000, 
              uint8_t mode = SPI_MODE_0, 
              uint8_t bits = 8,
              size_t transfer_size = 64,
              size_t buffer_size =  100);
    ~SpiReader();

    bool init();
    bool read_data();

    hardware_msg::msg::ImuState  get_imu_data();
    hardware_msg::msg::MotorsState get_motors_state_data();
    hardware_msg::msg::MotorsTelemetry get_motors_telemetries_data();


};

#endif