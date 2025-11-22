// spi_can_bridge.cpp
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/vector3.hpp>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>

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
        
        // Publishers (from SPI2CAN to ROS 2)
        joint_state_pub_ = this->create_publisher<sensor_msgs::msg::JointState>("/motors/states", 10);
        imu_pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("/imu/data", 10);
        
        // Subscribers (from ROS 2 GUI to SPI2CAN)
        commands_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/motors/commands", 10,
            std::bind(&SpiCanBridge::commands_callback, this, std::placeholders::_1));
            
        imu_commands_sub_ = this->create_subscription<std_msgs::msg::UInt8MultiArray>(
            "/imu/commands", 10,
            std::bind(&SpiCanBridge::imu_commands_callback, this, std::placeholders::_1));
            
        beep_sub_ = this->create_subscription<std_msgs::msg::Float32>(
            "/control_board/commands", 10,
            std::bind(&SpiCanBridge::beep_callback, this, std::placeholders::_1));

        // Timer for reading from shared memory and publishing to ROS
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&SpiCanBridge::timer_callback, this));
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

    void commands_callback(const sensor_msgs::msg::JointState::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Convert JointState to SPI2CAN shared memory format
        // This writes to the shared memory that SPI2CAN reads from
        write_joint_commands_to_shared_memory(msg);
    }

    void imu_commands_callback(const std_msgs::msg::UInt8MultiArray::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (msg->data.size() >= 3) {
            // Store IMU calibration commands to write to shared memory
            imu_calibration_[0] = msg->data[0]; // acc_calibrate
            imu_calibration_[1] = msg->data[1]; // mag_calibrate  
            imu_calibration_[2] = msg->data[2]; // gyro_calibrate
        }
    }

    void beep_callback(const std_msgs::msg::Float32::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        beep_state_ = msg->data;
    }

    void timer_callback() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Read from shared memory (data from SPI2CAN)
        if (shared_memory_ != nullptr) {
            read_from_shared_memory_and_publish();
        }
        
        // Write commands to shared memory (for SPI2CAN to read)
        write_commands_to_shared_memory();
    }

    void write_joint_commands_to_shared_memory(const sensor_msgs::msg::JointState::SharedPtr msg) {
        // Store the latest commands
        latest_commands_ = *msg;
        commands_updated_ = true;
    }

    void write_commands_to_shared_memory() {
        ShareMemory* shm = (ShareMemory*)shared_memory_;
        
        if (shm->flag == 0) {
            // Memory is ready for writing
            
            // Convert ROS 2 commands to SPI2CAN format
            // This is the reverse of the memory_read() function in SPI2CAN
            unsigned char write_buf[MEM_SIZE] = {0};
            int write_cnt = MEM_SIZE / 2; // Start at second half for commands
            
            // Write motor commands (10 motors)
            for (int i = 0; i < 10; i++) {
                float q_set = 0.0f, dq_set = 0.0f, tau_ff = 0.0f;
                
                if (i < latest_commands_.position.size()) {
                    q_set = latest_commands_.position[i];
                }
                if (i < latest_commands_.velocity.size()) {
                    dq_set = latest_commands_.velocity[i];
                }
                if (i < latest_commands_.effort.size()) {
                    tau_ff = latest_commands_.effort[i];
                }
                
                // Convert floats to bytes (same as SPI2CAN's setDataFloat_spi)
                write_float_to_buffer(write_buf, &write_cnt, q_set);
                write_float_to_buffer(write_buf, &write_cnt, dq_set);
                write_float_to_buffer(write_buf, &write_cnt, tau_ff);
            }
            
            // Write PID gains
            write_float_to_buffer(write_buf, &write_cnt, kp_);
            write_float_to_buffer(write_buf, &write_cnt, kd_);
            
            // Write control flags
            write_buf[write_cnt++] = en_motor_;
            write_buf[write_cnt++] = reset_q_;
            write_buf[write_cnt++] = reset_err_;
            
            // Write IMU calibration flags
            write_buf[write_cnt++] = imu_calibration_[0]; // Acc
            write_buf[write_cnt++] = imu_calibration_[1]; // Gyro
            write_buf[write_cnt++] = imu_calibration_[2]; // Mag
            
            // Write beep state
            write_buf[write_cnt++] = (uint8_t)beep_state_;
            
            // Copy to shared memory
            memcpy(&shm->szMsg[MEM_SIZE/2], write_buf, MEM_SIZE/2);
            shm->flag = 1; // Signal that data is ready
        }
    }

    void read_from_shared_memory_and_publish() {
        ShareMemory* shm = (ShareMemory*)shared_memory_;
        
        if (shm->flag == 1) {
            // Memory has fresh data from SPI2CAN
            
            // Parse the data (reverse of SPI2CAN's memory_write())
            unsigned char* read_buf = shm->szMsg;
            int read_cnt = 0;
            
            // Create JointState message for motor feedback
            auto joint_state_msg = sensor_msgs::msg::JointState();
            joint_state_msg.name.resize(10);
            joint_state_msg.position.resize(10);
            joint_state_msg.velocity.resize(10);
            joint_state_msg.effort.resize(10);
            
            // Read IMU data
            float pitch = read_float_from_buffer(read_buf, &read_cnt);
            float roll = read_float_from_buffer(read_buf, &read_cnt);
            float yaw = read_float_from_buffer(read_buf, &read_cnt);
            
            float pitch_rate = read_float_from_buffer(read_buf, &read_cnt);
            float roll_rate = read_float_from_buffer(read_buf, &read_cnt);
            float yaw_rate = read_float_from_buffer(read_buf, &read_cnt);
            
            float acc_x = read_float_from_buffer(read_buf, &read_cnt);
            float acc_y = read_float_from_buffer(read_buf, &read_cnt);
            float acc_z = read_float_from_buffer(read_buf, &read_cnt);
            
            // Read motor data (10 motors)
            for (int i = 0; i < 10; i++) {
                joint_state_msg.name[i] = "motor_" + std::to_string(i+1);
                joint_state_msg.position[i] = read_float_from_buffer(read_buf, &read_cnt);
                joint_state_msg.velocity[i] = read_float_from_buffer(read_buf, &read_cnt);
                joint_state_msg.effort[i] = read_float_from_buffer(read_buf, &read_cnt);
            }
            
            // Publish the messages
            joint_state_pub_->publish(joint_state_msg);
            
            // Publish IMU data
            auto imu_msg = geometry_msgs::msg::Vector3();
            imu_msg.x = pitch;
            imu_msg.y = roll;
            imu_msg.z = yaw;
            imu_pub_->publish(imu_msg);
            
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

    // ROS 2 interfaces
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr imu_pub_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr commands_sub_;
    rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr imu_commands_sub_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr beep_sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    // Shared memory
    int shmid_;
    void* shared_memory_;
    std::mutex mutex_;

    // Command state
    sensor_msgs::msg::JointState latest_commands_;
    bool commands_updated_ = false;
    uint8_t imu_calibration_[3] = {0};
    float beep_state_ = 0.0f;
    float kp_ = 0.0f, kd_ = 0.0f;
    uint8_t en_motor_ = 0, reset_q_ = 0, reset_err_ = 0;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SpiCanBridge>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
