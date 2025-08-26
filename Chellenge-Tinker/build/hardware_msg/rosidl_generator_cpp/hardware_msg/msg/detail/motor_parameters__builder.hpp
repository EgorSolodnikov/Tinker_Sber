// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/MotorParameters.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/motor_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_MotorParameters_kd
{
public:
  explicit Init_MotorParameters_kd(::hardware_msg::msg::MotorParameters & msg)
  : msg_(msg)
  {}
  ::hardware_msg::msg::MotorParameters kd(::hardware_msg::msg::MotorParameters::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::MotorParameters msg_;
};

class Init_MotorParameters_kp
{
public:
  explicit Init_MotorParameters_kp(::hardware_msg::msg::MotorParameters & msg)
  : msg_(msg)
  {}
  Init_MotorParameters_kd kp(::hardware_msg::msg::MotorParameters::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_MotorParameters_kd(msg_);
  }

private:
  ::hardware_msg::msg::MotorParameters msg_;
};

class Init_MotorParameters_reset_error
{
public:
  explicit Init_MotorParameters_reset_error(::hardware_msg::msg::MotorParameters & msg)
  : msg_(msg)
  {}
  Init_MotorParameters_kp reset_error(::hardware_msg::msg::MotorParameters::_reset_error_type arg)
  {
    msg_.reset_error = std::move(arg);
    return Init_MotorParameters_kp(msg_);
  }

private:
  ::hardware_msg::msg::MotorParameters msg_;
};

class Init_MotorParameters_reset_zero
{
public:
  explicit Init_MotorParameters_reset_zero(::hardware_msg::msg::MotorParameters & msg)
  : msg_(msg)
  {}
  Init_MotorParameters_reset_error reset_zero(::hardware_msg::msg::MotorParameters::_reset_zero_type arg)
  {
    msg_.reset_zero = std::move(arg);
    return Init_MotorParameters_reset_error(msg_);
  }

private:
  ::hardware_msg::msg::MotorParameters msg_;
};

class Init_MotorParameters_enable
{
public:
  Init_MotorParameters_enable()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorParameters_reset_zero enable(::hardware_msg::msg::MotorParameters::_enable_type arg)
  {
    msg_.enable = std::move(arg);
    return Init_MotorParameters_reset_zero(msg_);
  }

private:
  ::hardware_msg::msg::MotorParameters msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::MotorParameters>()
{
  return hardware_msg::msg::builder::Init_MotorParameters_enable();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__BUILDER_HPP_
