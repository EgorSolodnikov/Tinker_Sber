// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/MotorsCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motors_commands.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/motors_commands__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_MotorsCommands_target_trq
{
public:
  explicit Init_MotorsCommands_target_trq(::hardware_msg::msg::MotorsCommands & msg)
  : msg_(msg)
  {}
  ::hardware_msg::msg::MotorsCommands target_trq(::hardware_msg::msg::MotorsCommands::_target_trq_type arg)
  {
    msg_.target_trq = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::MotorsCommands msg_;
};

class Init_MotorsCommands_target_vel
{
public:
  explicit Init_MotorsCommands_target_vel(::hardware_msg::msg::MotorsCommands & msg)
  : msg_(msg)
  {}
  Init_MotorsCommands_target_trq target_vel(::hardware_msg::msg::MotorsCommands::_target_vel_type arg)
  {
    msg_.target_vel = std::move(arg);
    return Init_MotorsCommands_target_trq(msg_);
  }

private:
  ::hardware_msg::msg::MotorsCommands msg_;
};

class Init_MotorsCommands_target_pos
{
public:
  Init_MotorsCommands_target_pos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorsCommands_target_vel target_pos(::hardware_msg::msg::MotorsCommands::_target_pos_type arg)
  {
    msg_.target_pos = std::move(arg);
    return Init_MotorsCommands_target_vel(msg_);
  }

private:
  ::hardware_msg::msg::MotorsCommands msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::MotorsCommands>()
{
  return hardware_msg::msg::builder::Init_MotorsCommands_target_pos();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__BUILDER_HPP_
