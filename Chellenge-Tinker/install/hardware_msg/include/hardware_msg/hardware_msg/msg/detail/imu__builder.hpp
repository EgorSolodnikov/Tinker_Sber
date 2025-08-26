// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/Imu.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__IMU__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__IMU__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/imu__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_Imu_yaw
{
public:
  explicit Init_Imu_yaw(::hardware_msg::msg::Imu & msg)
  : msg_(msg)
  {}
  ::hardware_msg::msg::Imu yaw(::hardware_msg::msg::Imu::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::Imu msg_;
};

class Init_Imu_roll
{
public:
  explicit Init_Imu_roll(::hardware_msg::msg::Imu & msg)
  : msg_(msg)
  {}
  Init_Imu_yaw roll(::hardware_msg::msg::Imu::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_Imu_yaw(msg_);
  }

private:
  ::hardware_msg::msg::Imu msg_;
};

class Init_Imu_pitch
{
public:
  Init_Imu_pitch()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Imu_roll pitch(::hardware_msg::msg::Imu::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_Imu_roll(msg_);
  }

private:
  ::hardware_msg::msg::Imu msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::Imu>()
{
  return hardware_msg::msg::builder::Init_Imu_pitch();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU__BUILDER_HPP_
