// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hardware_msg:msg/MotorsStates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motors_states.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__TRAITS_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hardware_msg/msg/detail/motors_states__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hardware_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorsStates & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_pos
  {
    if (msg.current_pos.size() == 0) {
      out << "current_pos: []";
    } else {
      out << "current_pos: [";
      size_t pending_items = msg.current_pos.size();
      for (auto item : msg.current_pos) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: current_vel
  {
    if (msg.current_vel.size() == 0) {
      out << "current_vel: []";
    } else {
      out << "current_vel: [";
      size_t pending_items = msg.current_vel.size();
      for (auto item : msg.current_vel) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: current_trq
  {
    if (msg.current_trq.size() == 0) {
      out << "current_trq: []";
    } else {
      out << "current_trq: [";
      size_t pending_items = msg.current_trq.size();
      for (auto item : msg.current_trq) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorsStates & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_pos.size() == 0) {
      out << "current_pos: []\n";
    } else {
      out << "current_pos:\n";
      for (auto item : msg.current_pos) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: current_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_vel.size() == 0) {
      out << "current_vel: []\n";
    } else {
      out << "current_vel:\n";
      for (auto item : msg.current_vel) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: current_trq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_trq.size() == 0) {
      out << "current_trq: []\n";
    } else {
      out << "current_trq:\n";
      for (auto item : msg.current_trq) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorsStates & msg, bool use_flow_style = false)
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
  const hardware_msg::msg::MotorsStates & msg,
  std::ostream & out, size_t indentation = 0)
{
  hardware_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hardware_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const hardware_msg::msg::MotorsStates & msg)
{
  return hardware_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hardware_msg::msg::MotorsStates>()
{
  return "hardware_msg::msg::MotorsStates";
}

template<>
inline const char * name<hardware_msg::msg::MotorsStates>()
{
  return "hardware_msg/msg/MotorsStates";
}

template<>
struct has_fixed_size<hardware_msg::msg::MotorsStates>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hardware_msg::msg::MotorsStates>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hardware_msg::msg::MotorsStates>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__TRAITS_HPP_
