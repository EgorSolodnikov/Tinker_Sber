// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/imu_parameters.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__TRAITS_HPP_
#define HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "hardware_msg/msg/detail/imu_parameters__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace hardware_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const ImuParameters & msg,
  std::ostream & out)
{
  out << "{";
  // member: acc_calibrate
  {
    out << "acc_calibrate: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_calibrate, out);
    out << ", ";
  }

  // member: mag_calibrate
  {
    out << "mag_calibrate: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_calibrate, out);
    out << ", ";
  }

  // member: gyro_calibrate
  {
    out << "gyro_calibrate: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_calibrate, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ImuParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: acc_calibrate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "acc_calibrate: ";
    rosidl_generator_traits::value_to_yaml(msg.acc_calibrate, out);
    out << "\n";
  }

  // member: mag_calibrate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mag_calibrate: ";
    rosidl_generator_traits::value_to_yaml(msg.mag_calibrate, out);
    out << "\n";
  }

  // member: gyro_calibrate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_calibrate: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_calibrate, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ImuParameters & msg, bool use_flow_style = false)
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
  const hardware_msg::msg::ImuParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  hardware_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use hardware_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const hardware_msg::msg::ImuParameters & msg)
{
  return hardware_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<hardware_msg::msg::ImuParameters>()
{
  return "hardware_msg::msg::ImuParameters";
}

template<>
inline const char * name<hardware_msg::msg::ImuParameters>()
{
  return "hardware_msg/msg/ImuParameters";
}

template<>
struct has_fixed_size<hardware_msg::msg::ImuParameters>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hardware_msg::msg::ImuParameters>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hardware_msg::msg::ImuParameters>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__TRAITS_HPP_
