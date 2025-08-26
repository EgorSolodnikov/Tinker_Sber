// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/board_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_BoardParameters_beep_state
{
public:
  Init_BoardParameters_beep_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hardware_msg::msg::BoardParameters beep_state(::hardware_msg::msg::BoardParameters::_beep_state_type arg)
  {
    msg_.beep_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::BoardParameters msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::BoardParameters>()
{
  return hardware_msg::msg::builder::Init_BoardParameters_beep_state();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__BUILDER_HPP_
