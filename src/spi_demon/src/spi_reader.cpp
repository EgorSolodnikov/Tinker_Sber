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
        std::cerr << "SPI device not initialized" << std::endl;
        return false;
    }

    std::fill(tx_buffer_.begin(), tx_buffer_.end(), 0);

    struct spi_ioc_transfer transfer;
    transfer.tx_buf = reinterpret_cast<__u64>(tx_buffer_.data());
    transfer.rx_buf = reinterpret_cast<__u64>(rx_buffer_.data());
    transfer.len = static_cast<__u32>(transfer_size_);
    transfer.speed_hz = static_cast<__u32>(speed_);
    transfer.delay_usecs = static_cast<__u16>(0);
    transfer.bits_per_word = static_cast<__u8>(bits_per_word_);
    transfer.cs_change = static_cast<__u8>(0);
    transfer.tx_nbits = static_cast<__u8>(0);
    transfer.rx_nbits = static_cast<__u8>(0);
    transfer.word_delay_usecs = static_cast<__u8>(0);  // Add this
    transfer.pad = static_cast<__u16>(0);

    int ret = ioctl(spi_fd_, SPI_IOC_MESSAGE(1), &transfer);
    if (ret < 0) {
        std::cerr << "SPI transfer failed: " << strerror(errno) << std::endl;
        return false;
    }

    if (rx_buffer_.size() < 4) {
        std::cerr << "Buffer too small for header" << std::endl;
        return false;
    }

    const uint8_t* data = rx_buffer_.data();
    if (data[0] != 0xFF || data[1] != 0xFB) {
        std::cerr << "Invalid header" << std::endl;
        return false;
    }

    if (data[2] != 26) {
        std::cerr << "Invalid packet ID" << std::endl;
        return false;
    }

    uint8_t len = data[3];
    size_t expected_size = 4 + static_cast<size_t>(len) + 1;
    if (rx_buffer_.size() < expected_size) {
        std::cerr << "Buffer too small" << std::endl;
        return false;
    }

    // Additional check for minimal payload length (IMU 36 bytes + motors 70 bytes = 106 bytes)
    if (len < 106) {
        std::cerr << "Payload length too small for complete data: " << static_cast<int>(len) << " < 106" << std::endl;
        return false;
    }

    uint8_t sum = 0;
    for (size_t i = 0; i < expected_size - 1; ++i) {
        sum += data[i];
    }
    if (sum != data[expected_size - 1]) {
        std::cerr << "Checksum error" << std::endl;
        return false;
    }

    // Parse with potential exceptions or errors
    try {
        imu_buffer_.put(internal_parse_imu_data());
        motors_state_buffer_.put(internal_parse_motor_state_data());
        motors_telemetry_buffer_.put(internal_parse_motor_telemetry_data());
    } catch (const std::exception& e) {
        std::cerr << "Parsing exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}

// Helper for float parsing (big-endian wire format, as in original)
float SpiReader::parse_float(const uint8_t* data) const {
    uint32_t i = (static_cast<uint32_t>(data[3]) << 24) |
                 (static_cast<uint32_t>(data[2]) << 16) |
                 (static_cast<uint32_t>(data[1]) << 8) |
                 static_cast<uint32_t>(data[0]);
    float f;
    std::memcpy(&f, &i, sizeof(float));
    return f;
}

// Helper for int16 parsing (big-endian wire format, high byte first, as in original)
int16_t SpiReader::parse_int16(const uint8_t* data) const {
    return static_cast<int16_t>((static_cast<uint16_t>(data[0]) << 8) | data[1]);
}

hardware_msg::msg::ImuState SpiReader::internal_parse_imu_data() const {
    hardware_msg::msg::ImuState state;

    const uint8_t* data = rx_buffer_.data();
    size_t offset = 4;  // Start of payload
    size_t payload_end = rx_buffer_.size() - 1;  // Before checksum

    // Check for full IMU data (3 att + 3 rate + 3 acc = 9 floats = 36 bytes)
    if (offset + 36 > payload_end) {
        throw std::runtime_error("Buffer too small for IMU data");
    }

    // Parse att (roll, pitch, yaw)
    state.roll = parse_float(data + offset); offset += 4;
    state.pitch = parse_float(data + offset); offset += 4;
    state.yaw = parse_float(data + offset); offset += 4;

    // Skip att_rate and acc_b (less functional, but advance offset to match structure)
    offset += 24;  // 6 floats * 4 bytes

    return state;
}

hardware_msg::msg::MotorsState SpiReader::internal_parse_motor_state_data() const {
    hardware_msg::msg::MotorsState state;

    const uint8_t* data = rx_buffer_.data();
    constexpr size_t motor_start = 40;  // After 36 bytes of IMU
    constexpr size_t bytes_per_motor = 7;
    constexpr float POS_DIV = 30.0f;  // Based on CAN_POS_DIV (assumed value from provided code)
    constexpr float VEL_DIV = 30.0f;  // Based on CAN_DPOS_DIV (assumed)
    constexpr float TOR_DIV = 500.0f; // Based on CAN_T_DIV (assumed)

    size_t payload_end = rx_buffer_.size() - 1;  // Before checksum

    state.position.resize(10, 0.0f);
    state.velocity.resize(10, 0.0f);
    state.torque.resize(10, 0.0f);

    for (int i = 0; i < 10; ++i) {
        size_t offset = motor_start + static_cast<size_t>(i) * bytes_per_motor;

        // Check for buffer overflow before parsing q, dq, tau (6 bytes) + status (1 byte)
        if (offset + 7 > payload_end) {
            std::cerr << "Buffer overflow in motor state parsing for motor " << i << std::endl;
            // Fill remaining with defaults or throw
            throw std::runtime_error("Buffer overflow in motor state parsing");
        }

        int16_t q_raw = parse_int16(data + offset);
        int16_t dq_raw = parse_int16(data + offset + 2);
        int16_t tau_raw = parse_int16(data + offset + 4);

        state.position[i] = static_cast<float>(q_raw) / POS_DIV;
        state.velocity[i] = static_cast<float>(dq_raw) / VEL_DIV;
        state.torque[i] = static_cast<float>(tau_raw) / TOR_DIV;
    }

    return state;
}

hardware_msg::msg::MotorsTelemetry SpiReader::internal_parse_motor_telemetry_data() const {
    hardware_msg::msg::MotorsTelemetry telemetry;

    const uint8_t* data = rx_buffer_.data();
    constexpr size_t motor_start = 40;
    constexpr size_t bytes_per_motor = 7;

    size_t payload_end = rx_buffer_.size() - 1;

    telemetry.id.resize(10);
    telemetry.connect.resize(10);
    telemetry.motor_connected.resize(10);
    telemetry.ready.resize(10);

    for (int i = 0; i < 10; ++i) {
        size_t offset = motor_start + static_cast<size_t>(i) * bytes_per_motor + 6;  // Status byte

        // Check for buffer overflow for status byte
        if (offset >= payload_end) {
            std::cerr << "Buffer overflow in motor telemetry parsing for motor " << i << std::endl;
            throw std::runtime_error("Buffer overflow in motor telemetry parsing");
        }

        uint8_t status = data[offset];
        uint8_t connect_val = (status % 100) / 10;
        uint8_t ready_val = status % 10;

        telemetry.id[i] = static_cast<uint8_t>(i);
        telemetry.connect[i] = (connect_val != 0);
        telemetry.motor_connected[i] = (connect_val != 0);
        telemetry.ready[i] = (ready_val != 0);
    }

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