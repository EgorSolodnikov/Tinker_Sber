// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/MotorsStates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motors_states.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/motors_states__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_MotorsStates_current_trq
{
public:
  explicit Init_MotorsStates_current_trq(::hardware_msg::msg::MotorsStates & msg)
  : msg_(msg)
  {}
  ::hardware_msg::msg::MotorsStates current_trq(::hardware_msg::msg::MotorsStates::_current_trq_type arg)
  {
    msg_.current_trq = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::MotorsStates msg_;
};

class Init_MotorsStates_current_vel
{
public:
  explicit Init_MotorsStates_current_vel(::hardware_msg::msg::MotorsStates & msg)
  : msg_(msg)
  {}
  Init_MotorsStates_current_trq current_vel(::hardware_msg::msg::MotorsStates::_current_vel_type arg)
  {
    msg_.current_vel = std::move(arg);
    return Init_MotorsStates_current_trq(msg_);
  }

private:
  ::hardware_msg::msg::MotorsStates msg_;
};

class Init_MotorsStates_current_pos
{
public:
  Init_MotorsStates_current_pos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorsStates_current_vel current_pos(::hardware_msg::msg::MotorsStates::_current_pos_type arg)
  {
    msg_.current_pos = std::move(arg);
    return Init_MotorsStates_current_vel(msg_);
  }

private:
  ::hardware_msg::msg::MotorsStates msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::MotorsStates>()
{
  return hardware_msg::msg::builder::Init_MotorsStates_current_pos();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__BUILDER_HPP_
