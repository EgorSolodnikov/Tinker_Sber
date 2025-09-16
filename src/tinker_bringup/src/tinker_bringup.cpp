#include <vector>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

#include "hardware_msg/msg/imu_state.hpp"
#include "hardware_msg/msg/motors_state.hpp"
#include "hardware_msg/msg/motors_telemetry.hpp"


class MotorJointState : public rclcpp::Node
{
public:
    MotorJointState() : Node("motor_to_joint_state") {
        this->declare_parameter("joint_names", std::vector<std::string>{
            "joint_l_yaw", "joint_l_roll", "joint_l_pitch", "joint_l_knee", "joint_l_ankle", 
            "joint_r_yaw", "joint_r_roll", "joint_r_pitch", "joint_r_knee", "joint_r_ankle"});
        joint_names_ = this->get_parameter("joint_names").as_string_array();

        motors_state_sub_ = this->create_subscription<hardware_msg::msg::MotorsState>(
            "/motors_state", rclcpp::QoS(10), 
            [this](std::shared_ptr<hardware_msg::msg::MotorsState> msg) {
                this->motors_state_callback(*msg);
            });

        joint_state_pub_ = this->create_publisher<sensor_msgs::msg::JointState>(
            "joint_states", rclcpp::QoS(10));
    }

private:
    void motors_state_callback(const hardware_msg::msg::MotorsState &msg) {
        auto joint_state = sensor_msgs::msg::JointState();
        joint_state.header.stamp = this->now();
        joint_state.name = joint_names_;
        
        if (msg.position.size() >= joint_names_.size()) {
            joint_state.position.assign(
                msg.position.begin(), 
                msg.position.begin() + joint_names_.size()
            );
        } 
        else {
            RCLCPP_WARN(this->get_logger(), 
                       "Not enough position values: expected %zu, got %zu", 
                       joint_names_.size(), msg.position.size());
            return;
        }
        
        if (msg.velocity.size() >= joint_names_.size()) {
            joint_state.velocity.assign(
                msg.velocity.begin(), 
                msg.velocity.begin() + joint_names_.size()
            );
        }
        
        if (msg.torque.size() >= joint_names_.size()) {
            joint_state.effort.assign(
                msg.torque.begin(), 
                msg.torque.begin() + joint_names_.size()
            );
        }
        
        joint_state_pub_->publish(joint_state);
    }
    
    std::vector<std::string> joint_names_;
    rclcpp::Subscription<hardware_msg::msg::MotorsState>::SharedPtr motors_state_sub_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MotorJointState>());
    rclcpp::shutdown();
    return 0;
}