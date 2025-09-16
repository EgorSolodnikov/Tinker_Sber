#include "spi_demon/spi_reader.hpp"


SpiReader::SpiReader(const std::string& device, 
              uint32_t speed, 
              uint8_t mode,
              uint8_t bits,
              size_t transfer_size,
              size_t buffer_size)
    : device_(device), speed_(speed), mode_(mode)
    , bits_per_word_(bits), transfer_size_(transfer_size)
    ,  spi_fd_(-1)
    , imu_buffer_(buffer_size)
    , motors_state_buffer_(buffer_size)
    , motors_telemetry_buffer_(buffer_size)
{
    tx_buffer_.resize(transfer_size_, 0);
    rx_buffer_.resize(transfer_size_, 0);
}

SpiReader::~SpiReader() 
{
    if (spi_fd_ >= 0) 
    {
        close(spi_fd_);
    }
}

bool SpiReader::init()
{
    spi_fd_ = open(device_.c_str(), O_RDWR);
    if (spi_fd_ < 0) {
        throw std::runtime_error("Failed to open SPI device: " + device_);
        return false;
    }

    if (ioctl(spi_fd_, SPI_IOC_WR_MODE, &mode_) == -1) {
        throw std::runtime_error("Failed to set SPI mode");
        return false;
    }

    if (ioctl(spi_fd_, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word_) == -1) {
        throw std::runtime_error("Failed to set SPI bits per word");
        return false;
    }

    if (ioctl(spi_fd_, SPI_IOC_WR_MAX_SPEED_HZ, &speed_) == -1) {
        throw std::runtime_error("Failed to set SPI speed");
        return false;
    }

    return true;
}

bool SpiReader::read_data() {
    if (spi_fd_ < 0) {
        return false;
    }

    struct spi_ioc_transfer transfer = {
        .tx_buf = reinterpret_cast<unsigned long>(tx_buffer_.data()),
        .rx_buf = reinterpret_cast<unsigned long>(rx_buffer_.data()),
        .len = static_cast<uint32_t>(transfer_size_),
        .speed_hz = speed_,
        .delay_usecs = 0,
        .bits_per_word = bits_per_word_,
        .cs_change = 0,
        .tx_nbits = 0,
        .rx_nbits = 0,
        .word_delay_usecs = 0,
        .pad = 0,
    };

    if (ioctl(spi_fd_, SPI_IOC_MESSAGE(1), &transfer) < 0) {
        throw std::runtime_error("SPI transfer failed");
        return false;
    }

    imu_buffer_.put(internal_parse_imu_data());
    motors_state_buffer_.put(internal_parse_motor_state_data());
    motors_telemetry_buffer_.put(internal_parse_motor_telemetry_data());
    return true;
}

// Implement these functions
hardware_msg::msg::ImuState SpiReader::internal_parse_imu_data() const
{
    hardware_msg::msg::ImuState state;
    // Parse IMU data from rx_buffer_
    return state;
}

hardware_msg::msg::MotorsState SpiReader::internal_parse_motor_state_data() const
{
    hardware_msg::msg::MotorsState state;
    // Parse motor state data from rx_buffer_
    return state;
}

hardware_msg::msg::MotorsTelemetry SpiReader::internal_parse_motor_telemetry_data() const
{
    hardware_msg::msg::MotorsTelemetry telemetry;
    // Parse motor telemetry data from rx_buffer_
    return telemetry;
}


hardware_msg::msg::ImuState SpiReader::get_imu_data()
{
    return imu_buffer_.get();
}

hardware_msg::msg::MotorsState SpiReader::get_motors_state_data()
{
    return motors_state_buffer_.get();
}

hardware_msg::msg::MotorsTelemetry SpiReader::get_motors_telemetries_data()
{
    return motors_telemetry_buffer_.get();
}