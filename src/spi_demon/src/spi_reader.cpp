#include "spi_demon/spi_reader.hpp"


SpiReader::SpiReader(const std::string& device, 
                     uint32_t speed, 
                     uint8_t mode, 
                     uint8_t bits, 
                     size_t transfer_size, 
                     size_t buffer_size)
    : device_(device), speed_(speed), mode_(mode), spi_fd_(-1), bits_per_word_(bits), transfer_size_(transfer_size),
      imu_buffer_(buffer_size), motors_state_buffer_(buffer_size), motors_telemetry_buffer_(buffer_size) {
    tx_buffer_.resize(transfer_size_, 0);
    rx_buffer_.resize(transfer_size_, 0);
}

SpiReader::~SpiReader() {
    if (spi_fd_ >= 0) {
        close(spi_fd_);
    }
}

bool SpiReader::init() {
    spi_fd_ = open(device_.c_str(), O_RDWR);
    if (spi_fd_ < 0) {
        throw std::runtime_error("Failed to open SPI device: " + device_);
    }

    if (ioctl(spi_fd_, SPI_IOC_WR_MODE, &mode_) == -1) {
        close(spi_fd_);
        spi_fd_ = -1;
        throw std::runtime_error("Failed to set SPI mode");
    }

    if (ioctl(spi_fd_, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word_) == -1) {
        close(spi_fd_);
        spi_fd_ = -1;
        throw std::runtime_error("Failed to set SPI bits per word");
    }

    if (ioctl(spi_fd_, SPI_IOC_WR_MAX_SPEED_HZ, &speed_) == -1) {
        close(spi_fd_);
        spi_fd_ = -1;
        throw std::runtime_error("Failed to set SPI speed");
    }

    return true;
}

bool SpiReader::read_data() {
    if (spi_fd_ < 0) {
        return false;
    }

    // Clear tx_buffer_ 
    std::fill(tx_buffer_.begin(), tx_buffer_.end(), 0);

    struct spi_ioc_transfer transfer = {
        reinterpret_cast<__u64>(tx_buffer_.data()),
        reinterpret_cast<__u64>(rx_buffer_.data()),
        static_cast<__u32>(transfer_size_),
        static_cast<__u32>(speed_),
        static_cast<__u16>(0),
        static_cast<__u8>(bits_per_word_),
        static_cast<__u8>(0),
        static_cast<__u8>(0),
        static_cast<__u8>(0),
        static_cast<__u16>(0),
        static_cast<__u32>(0)
    };

    int ret = ioctl(spi_fd_, SPI_IOC_MESSAGE(1), &transfer);
    if (ret < 0) {
        std::cerr << "SPI transfer failed with error: " << strerror(errno) << std::endl;
        return false;
    }
    if (ret != 1) {
        std::cerr << "SPI transfer incomplete: " << ret << " transfers succeeded" << std::endl;
        return false;
    }

    // Basic check: ensure we received at least header
    if (rx_buffer_.size() < 4) {
        std::cerr << "Received buffer too small for header" << std::endl;
        return false;
    }

    const uint8_t* data = rx_buffer_.data();
    uint8_t len = data[3];
    size_t expected_size = 4 + static_cast<size_t>(len) + 1;  // + checksum
    if (rx_buffer_.size() < expected_size) {
        std::cerr << "Received buffer too small: " << rx_buffer_.size() << " < " << expected_size << std::endl;
        return false;
    }

    // Debug: print first few bytes
    std::cerr << "Received SPI data (first 10 bytes): ";
    for (size_t i = 0; i < 10 && i < rx_buffer_.size(); ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
    }
    std::cerr << std::dec << std::endl;

    // Check header
    if (data[0] != 0xFF || data[1] != 0xFB) {
        std::cerr << "Invalid SPI header: expected 0xFF 0xFB, got 0x" 
                  << std::hex << static_cast<int>(data[0]) << " 0x" << static_cast<int>(data[1]) << std::dec << std::endl;
        return false;
    }

    // TODO: Add checksum verification (sum or XOR of data[0..120] == data[121]?)

    // Parse and put to buffers
    try {
        imu_buffer_.put(internal_parse_imu_data());
        motors_state_buffer_.put(internal_parse_motor_state_data());
        motors_telemetry_buffer_.put(internal_parse_motor_telemetry_data());
    } catch (const std::exception& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

// Implement these functions
hardware_msg::msg::ImuState SpiReader::internal_parse_imu_data() const {
    hardware_msg::msg::ImuState state(rosidl_runtime_cpp::MessageInitialization::ZERO);

    if (rx_buffer_.size() < 16) {  // At least up to yaw (bytes 0-15)
        std::cerr << "Buffer too small for IMU data" << std::endl;
        return state;
    }

    const uint8_t* data = rx_buffer_.data();

    // Header already checked in read_data

    uint8_t len = data[3];
    if (rx_buffer_.size() < 4u + static_cast<size_t>(len) + 1u) {
        std::cerr << "Buffer size " << rx_buffer_.size() << " smaller than header + len + checksum " << (4u + static_cast<size_t>(len) + 1u) << std::endl;
        return state;
    }

    if (4u + static_cast<size_t>(len) < 16u) {
        std::cerr << "Data length too small for IMU" << std::endl;
        return state;
    }

    // Parse angles: roll (4-7), pitch (8-11), yaw (12-15)
    float roll_f, pitch_f, yaw_f;
    std::memcpy(&roll_f, data + 4, sizeof(float));
    std::memcpy(&pitch_f, data + 8, sizeof(float));
    std::memcpy(&yaw_f, data + 12, sizeof(float));

    state.pitch = pitch_f;
    state.roll = roll_f;
    state.yaw = yaw_f;

    // Debug print
    std::cerr << "Parsed IMU: pitch=" << state.pitch << ", roll=" << state.roll << ", yaw=" << state.yaw << std::endl;

    return state;
}

hardware_msg::msg::MotorsState SpiReader::internal_parse_motor_state_data() const {
    hardware_msg::msg::MotorsState state(rosidl_runtime_cpp::MessageInitialization::ZERO);

    if (rx_buffer_.size() < 110) {  // Up to end of motor data (40-109)
        std::cerr << "Buffer too small for motor state data" << std::endl;
        return state;
    }

    const uint8_t* data = rx_buffer_.data();

    // Header already checked

    uint8_t len = data[3];
    if (rx_buffer_.size() < 4u + static_cast<size_t>(len) + 1u || 4u + static_cast<size_t>(len) < 110u) {
        std::cerr << "Invalid length for motor state: " << static_cast<int>(len) << std::endl;
        return state;
    }

    constexpr size_t motor_start = 40;
    constexpr size_t bytes_per_motor = 7;

    state.position.resize(10);
    state.velocity.resize(10);
    state.torque.resize(10);

    for (int i = 0; i < 10; ++i) {
        size_t offset = motor_start + i * bytes_per_motor;

        int16_t q_raw, dq_raw, tau_raw;
        std::memcpy(&q_raw, data + offset, sizeof(int16_t));
        std::memcpy(&dq_raw, data + offset + 2, sizeof(int16_t));
        std::memcpy(&tau_raw, data + offset + 4, sizeof(int16_t));

        state.position[i] = static_cast<float>(q_raw) / 30.0f;
        state.velocity[i] = static_cast<float>(dq_raw) / 30.0f;
        state.torque[i] = static_cast<float>(tau_raw) / 500.0f;
    }

    // Debug: print first motor
    std::cerr << "Parsed Motor 0 state: pos=" << state.position[0] << ", vel=" << state.velocity[0] << ", tor=" << state.torque[0] << std::endl;

    return state;
}

hardware_msg::msg::MotorsTelemetry SpiReader::internal_parse_motor_telemetry_data() const {
    hardware_msg::msg::MotorsTelemetry telemetry(rosidl_runtime_cpp::MessageInitialization::ZERO);

    if (rx_buffer_.size() < 110) {
        std::cerr << "Buffer too small for motor telemetry data" << std::endl;
        return telemetry;
    }

    const uint8_t* data = rx_buffer_.data();

    // Header already checked

    uint8_t len = data[3];
    if (rx_buffer_.size() < 4u + static_cast<size_t>(len) + 1u || 4u + static_cast<size_t>(len) < 110u) {
        std::cerr << "Invalid length for motor telemetry: " << static_cast<int>(len) << std::endl;
        return telemetry;
    }

    constexpr size_t motor_start = 40;
    constexpr size_t bytes_per_motor = 7;

    telemetry.id.resize(10);
    telemetry.connect.resize(10);
    telemetry.motor_connected.resize(10);
    telemetry.ready.resize(10);

    for (int i = 0; i < 10; ++i) {
        telemetry.id[i] = static_cast<uint8_t>(i);

        size_t offset = motor_start + i * bytes_per_motor + 6;  // Status at +6

        uint8_t status = data[offset];
        bool is_connected = (status / 10u) != 0;
        bool is_ready = (status % 10u) != 0;

        telemetry.connect[i] = is_connected;
        telemetry.motor_connected[i] = is_connected;  // Assuming same as connect
        telemetry.ready[i] = is_ready;
    }

    // Debug: print first motor telemetry
    std::cerr << "Parsed Motor 0 telemetry: connected=" << (telemetry.connect[0] ? "true" : "false") 
              << ", motor_connected=" << (telemetry.motor_connected[0] ? "true" : "false") 
              << ", ready=" << (telemetry.ready[0] ? "true" : "false") << std::endl;

    return telemetry;
}

hardware_msg::msg::ImuState SpiReader::get_imu_data() {
    return imu_buffer_.get();
}

hardware_msg::msg::MotorsState SpiReader::get_motors_state_data() {
    return motors_state_buffer_.get();
}

hardware_msg::msg::MotorsTelemetry SpiReader::get_motors_telemetries_data() {
    return motors_telemetry_buffer_.get();
}