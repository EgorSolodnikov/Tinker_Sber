// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/MotorData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motor_data.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/motor_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_MotorData_ready
{
public:
  explicit Init_MotorData_ready(::hardware_msg::msg::MotorData & msg)
  : msg_(msg)
  {}
  ::hardware_msg::msg::MotorData ready(::hardware_msg::msg::MotorData::_ready_type arg)
  {
    msg_.ready = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::MotorData msg_;
};

class Init_MotorData_motor_connected
{
public:
  explicit Init_MotorData_motor_connected(::hardware_msg::msg::MotorData & msg)
  : msg_(msg)
  {}
  Init_MotorData_ready motor_connected(::hardware_msg::msg::MotorData::_motor_connected_type arg)
  {
    msg_.motor_connected = std::move(arg);
    return Init_MotorData_ready(msg_);
  }

private:
  ::hardware_msg::msg::MotorData msg_;
};

class Init_MotorData_connect
{
public:
  explicit Init_MotorData_connect(::hardware_msg::msg::MotorData & msg)
  : msg_(msg)
  {}
  Init_MotorData_motor_connected connect(::hardware_msg::msg::MotorData::_connect_type arg)
  {
    msg_.connect = std::move(arg);
    return Init_MotorData_motor_connected(msg_);
  }

private:
  ::hardware_msg::msg::MotorData msg_;
};

class Init_MotorData_id
{
public:
  Init_MotorData_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorData_connect id(::hardware_msg::msg::MotorData::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_MotorData_connect(msg_);
  }

private:
  ::hardware_msg::msg::MotorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::MotorData>()
{
  return hardware_msg::msg::builder::Init_MotorData_id();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
