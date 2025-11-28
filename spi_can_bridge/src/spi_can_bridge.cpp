// spi_can_bridge.cpp
#include <rclcpp/rclcpp.hpp>
#include <builtin_interfaces/msg/time.hpp>

// Custom message includes
#include "tinker_msgs/msg/control_cmd.hpp"
#include "tinker_msgs/msg/imu_state.hpp"
#include "tinker_msgs/msg/low_cmd.hpp"
#include "tinker_msgs/msg/low_state.hpp"
#include "tinker_msgs/msg/motor_cmd.hpp"
#include "tinker_msgs/msg/motor_state.hpp"
#include "tinker_msgs/msg/one_motor_cmd.hpp"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>
#include <array>

#define MEM_SPI 0001
#define MEM_SIZE 2048

struct ShareMemory {
    int flag;
    unsigned char szMsg[MEM_SIZE];
};

class SpiCanBridge : public rclcpp::Node {
public:
    SpiCanBridge() : Node("spi_can_bridge") {
        // Initialize shared memory
        initialize_shared_memory();
        
        // Publishers (from SPI2CAN to ROS 2) - using custom messages
        low_state_pub_ = this->create_publisher<tinker_msgs::msg::LowState>("/low_level_state", 10);
        
        // Subscribers (from ROS 2 GUI to SPI2CAN) - using custom messages
        low_cmd_sub_ = this->create_subscription<tinker_msgs::msg::LowCmd>(
            "/low_level_command", 10,
            std::bind(&SpiCanBridge::low_cmd_callback, this, std::placeholders::_1));
            
        control_cmd_sub_ = this->create_subscription<tinker_msgs::msg::ControlCmd>(
            "/control_command", 10,
            std::bind(&SpiCanBridge::control_cmd_callback, this, std::placeholders::_1));
            
        one_motor_cmd_sub_ = this->create_subscription<tinker_msgs::msg::OneMotorCmd>(
            "/single_motor_command", 10,
            std::bind(&SpiCanBridge::one_motor_cmd_callback, this, std::placeholders::_1));

        // Timer for reading from shared memory and publishing to ROS
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&SpiCanBridge::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "SPI CAN Bridge started with custom messages");
    }

private:
    void initialize_shared_memory() {
        // Get shared memory segment (same as in SPI2CAN node)
        shmid_ = shmget((key_t)MEM_SPI, sizeof(ShareMemory), 0666 | IPC_CREAT);
        if (shmid_ == -1) {
            RCLCPP_ERROR(this->get_logger(), "Failed to get shared memory segment");
            return;
        }
        
        shared_memory_ = shmat(shmid_, (void*)0, 0);
        if (shared_memory_ == (void*)-1) {
            RCLCPP_ERROR(this->get_logger(), "Failed to attach shared memory");
            return;
        }
        
        RCLCPP_INFO(this->get_logger(), "Shared memory attached successfully");
    }

    void low_cmd_callback(const tinker_msgs::msg::LowCmd::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Store the latest low level command
        latest_low_cmd_ = *msg;
        low_cmd_updated_ = true;
        
        RCLCPP_DEBUG(this->get_logger(), "Received LowCmd for %zu motors", msg->motor_cmd.size());
    }

    void control_cmd_callback(const tinker_msgs::msg::ControlCmd::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Store control command (enable/disable/clear error, etc.)
        latest_control_cmd_ = *msg;
        control_cmd_updated_ = true;
        
        RCLCPP_DEBUG(this->get_logger(), "Received ControlCmd: motor_id=%d, cmd=%d", 
                     msg->motor_id, msg->cmd);
    }

    void one_motor_cmd_callback(const tinker_msgs::msg::OneMotorCmd::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Store single motor command
        latest_one_motor_cmd_ = *msg;
        one_motor_cmd_updated_ = true;
        
        RCLCPP_DEBUG(this->get_logger(), "Received OneMotorCmd for motor %d", msg->motor_id);
    }

    void timer_callback() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Read from shared memory (data from SPI2CAN) and publish custom messages
        if (shared_memory_ != nullptr) {
            read_from_shared_memory_and_publish();
        }
        
        // Write commands to shared memory (for SPI2CAN to read)
        write_commands_to_shared_memory();
    }

    void write_commands_to_shared_memory() {
        ShareMemory* shm = (ShareMemory*)shared_memory_;
        
        if (shm->flag == 0) {
            // Memory is ready for writing
            
            // Convert custom ROS 2 messages to SPI2CAN format
            unsigned char write_buf[MEM_SIZE] = {0};
            int write_cnt = MEM_SIZE / 2; // Start at second half for commands
            
            // Write motor commands based on received message types
            if (low_cmd_updated_) {
                // Write LowCmd (all motors)
                write_low_cmd_to_buffer(write_buf, &write_cnt);
                low_cmd_updated_ = false;
            } 
            else if (one_motor_cmd_updated_) {
                // Write OneMotorCmd (single motor)
                write_one_motor_cmd_to_buffer(write_buf, &write_cnt);
                one_motor_cmd_updated_ = false;
            }
            
            // Write control commands if any
            if (control_cmd_updated_) {
                write_control_cmd_to_buffer(write_buf, &write_cnt);
                control_cmd_updated_ = false;
            }
            
            // Copy to shared memory
            memcpy(&shm->szMsg[MEM_SIZE/2], write_buf, MEM_SIZE/2);
            shm->flag = 1; // Signal that data is ready
        }
    }

    void write_low_cmd_to_buffer(unsigned char* buffer, int* cnt) {
        // Write all motor commands from LowCmd
        for (const auto& motor_cmd : latest_low_cmd_.motor_cmd) {
            write_float_to_buffer(buffer, cnt, motor_cmd.position);
            write_float_to_buffer(buffer, cnt, motor_cmd.velocity);
            write_float_to_buffer(buffer, cnt, motor_cmd.torque);
            write_float_to_buffer(buffer, cnt, motor_cmd.kp);
            write_float_to_buffer(buffer, cnt, motor_cmd.kd);
        }
        
        // Write control flags (simplified - you might want to map these from your messages)
        buffer[(*cnt)++] = 1; // enable flag
        buffer[(*cnt)++] = 0; // reset zero flag  
        buffer[(*cnt)++] = 0; // reset error flag
    }

    void write_one_motor_cmd_to_buffer(unsigned char* buffer, int* cnt) {
        // Write single motor command - position it correctly in the buffer
        int motor_offset = latest_one_motor_cmd_.motor_id * 20; // 5 floats * 4 bytes per motor
        
        // Ensure we don't overflow
        if (motor_offset + 20 < MEM_SIZE/2) {
            int temp_cnt = *cnt + motor_offset;
            
            write_float_to_buffer(buffer, &temp_cnt, latest_one_motor_cmd_.position);
            write_float_to_buffer(buffer, &temp_cnt, latest_one_motor_cmd_.velocity);
            write_float_to_buffer(buffer, &temp_cnt, latest_one_motor_cmd_.torque);
            write_float_to_buffer(buffer, &temp_cnt, latest_one_motor_cmd_.kp);
            write_float_to_buffer(buffer, &temp_cnt, latest_one_motor_cmd_.kd);
        }
        
        // Still write control flags
        buffer[(*cnt)++] = 1; // enable flag
        buffer[(*cnt)++] = 0; // reset zero flag
        buffer[(*cnt)++] = 0; // reset error flag
    }

    void write_control_cmd_to_buffer(unsigned char* buffer, int* cnt) {
        // Map ControlCmd to appropriate flags in the buffer
        switch (latest_control_cmd_.cmd) {
            case 252: // ENABLE
                buffer[(*cnt)++] = 1; // enable flag
                break;
            case 253: // DISABLE
                buffer[(*cnt)++] = 0; // enable flag
                break;
            case 254: // SET_ZERO_POSITION
                buffer[(*cnt)++] = 1; // reset zero flag
                break;
            case 251: // CLEAR_ERROR
                buffer[(*cnt)++] = 1; // reset error flag
                break;
        }
    }

    void read_from_shared_memory_and_publish() {
        ShareMemory* shm = (ShareMemory*)shared_memory_;
        
        if (shm->flag == 1) {
            // Memory has fresh data from SPI2CAN
            
            // Parse the data and create custom messages
            unsigned char* read_buf = shm->szMsg;
            int read_cnt = 0;
            
            // Create LowState message
            auto low_state_msg = tinker_msgs::msg::LowState();
            
            // Set timestamp
            auto now = this->now();
            low_state_msg.timestamp_state.sec = now.seconds();
            low_state_msg.timestamp_state.nanosec = now.nanoseconds() % 1000000000;
            
            low_state_msg.tick = tick_counter_++;
            
            // Read IMU data and create IMUState
            auto imu_state = tinker_msgs::msg::IMUState();
            imu_state.timestamp_state = low_state_msg.timestamp_state;
            
            // Read IMU quaternion (fixed arrays, use direct assignment)
            for (int i = 0; i < 4; i++) {
                imu_state.quaternion[i] = read_float_from_buffer(read_buf, &read_cnt);
            }
            
            // Read IMU gyroscope (fixed arrays, use direct assignment)
            for (int i = 0; i < 3; i++) {
                imu_state.gyroscope[i] = read_float_from_buffer(read_buf, &read_cnt);
            }
            
            // Read IMU accelerometer (fixed arrays, use direct assignment)
            for (int i = 0; i < 3; i++) {
                imu_state.accelerometer[i] = read_float_from_buffer(read_buf, &read_cnt);
            }
            
            // Read IMU RPY (fixed arrays, use direct assignment)
            for (int i = 0; i < 3; i++) {
                imu_state.rpy[i] = read_float_from_buffer(read_buf, &read_cnt);
            }
            
            // Read IMU temperature
            imu_state.temperature = static_cast<int16_t>(read_float_from_buffer(read_buf, &read_cnt));
            
            low_state_msg.imu_state = imu_state;
            
            // Read motor data (10 motors) - fixed array, use direct assignment
            for (int i = 0; i < 10; i++) {
                auto motor_state = tinker_msgs::msg::MotorState();
                motor_state.timestamp_state = low_state_msg.timestamp_state;
                
                motor_state.position = read_float_from_buffer(read_buf, &read_cnt);
                motor_state.velocity = read_float_from_buffer(read_buf, &read_cnt);
                motor_state.torque = read_float_from_buffer(read_buf, &read_cnt);
                motor_state.temperature_mosfet = static_cast<int16_t>(read_float_from_buffer(read_buf, &read_cnt));
                motor_state.temperature_rotor = static_cast<int16_t>(read_float_from_buffer(read_buf, &read_cnt));
                motor_state.error = static_cast<uint8_t>(read_float_from_buffer(read_buf, &read_cnt));
                
                low_state_msg.motor_state[i] = motor_state;
            }
            
            // Publish the LowState message
            low_state_pub_->publish(low_state_msg);
            
            shm->flag = 0; // Signal that we've read the data
        }
    }

    void write_float_to_buffer(unsigned char* buffer, int* cnt, float value) {
        int i = *(int*)&value;
        buffer[(*cnt)++] = ((i << 24) >> 24);
        buffer[(*cnt)++] = ((i << 16) >> 24);
        buffer[(*cnt)++] = ((i << 8) >> 24);
        buffer[(*cnt)++] = (i >> 24);
    }

    float read_float_from_buffer(unsigned char* buffer, int* cnt) {
        int i = 0x00;
        i |= (buffer[(*cnt) + 3] << 24);
        i |= (buffer[(*cnt) + 2] << 16);
        i |= (buffer[(*cnt) + 1] << 8);
        i |= (buffer[(*cnt) + 0]);
        *cnt += 4;
        return *(float*)&i;
    }

    // ROS 2 interfaces - using custom messages
    rclcpp::Publisher<tinker_msgs::msg::LowState>::SharedPtr low_state_pub_;
    
    rclcpp::Subscription<tinker_msgs::msg::LowCmd>::SharedPtr low_cmd_sub_;
    rclcpp::Subscription<tinker_msgs::msg::ControlCmd>::SharedPtr control_cmd_sub_;
    rclcpp::Subscription<tinker_msgs::msg::OneMotorCmd>::SharedPtr one_motor_cmd_sub_;
    
    rclcpp::TimerBase::SharedPtr timer_;

    // Shared memory
    int shmid_;
    void* shared_memory_;
    std::mutex mutex_;

    // Command state - using custom messages
    tinker_msgs::msg::LowCmd latest_low_cmd_;
    tinker_msgs::msg::ControlCmd latest_control_cmd_;
    tinker_msgs::msg::OneMotorCmd latest_one_motor_cmd_;
    
    bool low_cmd_updated_ = false;
    bool control_cmd_updated_ = false;
    bool one_motor_cmd_updated_ = false;
    
    uint32_t tick_counter_ = 0;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SpiCanBridge>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
