// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hardware_msg:msg/MotorParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motor_parameters.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__TRAITS_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hardware_msg/msg/detail/motor_parameters__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hardware_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorParameters & msg,
  std::ostream & out)
{
  out << "{";
  // member: enable
  {
    out << "enable: ";
    rosidl_generator_traits::value_to_yaml(msg.enable, out);
    out << ", ";
  }

  // member: reset_zero
  {
    out << "reset_zero: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_zero, out);
    out << ", ";
  }

  // member: reset_error
  {
    out << "reset_error: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_error, out);
    out << ", ";
  }

  // member: kp
  {
    out << "kp: ";
    rosidl_generator_traits::value_to_yaml(msg.kp, out);
    out << ", ";
  }

  // member: kd
  {
    out << "kd: ";
    rosidl_generator_traits::value_to_yaml(msg.kd, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: enable
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable: ";
    rosidl_generator_traits::value_to_yaml(msg.enable, out);
    out << "\n";
  }

  // member: reset_zero
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_zero: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_zero, out);
    out << "\n";
  }

  // member: reset_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_error: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_error, out);
    out << "\n";
  }

  // member: kp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kp: ";
    rosidl_generator_traits::value_to_yaml(msg.kp, out);
    out << "\n";
  }

  // member: kd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kd: ";
    rosidl_generator_traits::value_to_yaml(msg.kd, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorParameters & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace hardware_msg

namespace rosidl_generator_traits
{

[[deprecated("use hardware_msg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const hardware_msg::msg::MotorParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  hardware_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hardware_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const hardware_msg::msg::MotorParameters & msg)
{
  return hardware_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hardware_msg::msg::MotorParameters>()
{
  return "hardware_msg::msg::MotorParameters";
}

template<>
inline const char * name<hardware_msg::msg::MotorParameters>()
{
  return "hardware_msg/msg/MotorParameters";
}

template<>
struct has_fixed_size<hardware_msg::msg::MotorParameters>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hardware_msg::msg::MotorParameters>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hardware_msg::msg::MotorParameters>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__TRAITS_HPP_
