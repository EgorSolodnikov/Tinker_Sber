// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__TRAITS_HPP_
#define HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hardware_msg/msg/detail/board_parameters__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hardware_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const BoardParameters & msg,
  std::ostream & out)
{
  out << "{";
  // member: beep_state
  {
    out << "beep_state: ";
    rosidl_generator_traits::value_to_yaml(msg.beep_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BoardParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: beep_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "beep_state: ";
    rosidl_generator_traits::value_to_yaml(msg.beep_state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BoardParameters & msg, bool use_flow_style = false)
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
  const hardware_msg::msg::BoardParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  hardware_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hardware_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const hardware_msg::msg::BoardParameters & msg)
{
  return hardware_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hardware_msg::msg::BoardParameters>()
{
  return "hardware_msg::msg::BoardParameters";
}

template<>
inline const char * name<hardware_msg::msg::BoardParameters>()
{
  return "hardware_msg/msg/BoardParameters";
}

template<>
struct has_fixed_size<hardware_msg::msg::BoardParameters>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hardware_msg::msg::BoardParameters>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hardware_msg::msg::BoardParameters>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__TRAITS_HPP_
