// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/imu_parameters.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__BUILDER_HPP_
#define HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hardware_msg/msg/detail/imu_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hardware_msg
{

namespace msg
{

namespace builder
{

class Init_ImuParameters_gyro_calibrate
{
public:
  explicit Init_ImuParameters_gyro_calibrate(::hardware_msg::msg::ImuParameters & msg)
  : msg_(msg)
  {}
  ::hardware_msg::msg::ImuParameters gyro_calibrate(::hardware_msg::msg::ImuParameters::_gyro_calibrate_type arg)
  {
    msg_.gyro_calibrate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hardware_msg::msg::ImuParameters msg_;
};

class Init_ImuParameters_mag_calibrate
{
public:
  explicit Init_ImuParameters_mag_calibrate(::hardware_msg::msg::ImuParameters & msg)
  : msg_(msg)
  {}
  Init_ImuParameters_gyro_calibrate mag_calibrate(::hardware_msg::msg::ImuParameters::_mag_calibrate_type arg)
  {
    msg_.mag_calibrate = std::move(arg);
    return Init_ImuParameters_gyro_calibrate(msg_);
  }

private:
  ::hardware_msg::msg::ImuParameters msg_;
};

class Init_ImuParameters_acc_calibrate
{
public:
  Init_ImuParameters_acc_calibrate()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ImuParameters_mag_calibrate acc_calibrate(::hardware_msg::msg::ImuParameters::_acc_calibrate_type arg)
  {
    msg_.acc_calibrate = std::move(arg);
    return Init_ImuParameters_mag_calibrate(msg_);
  }

private:
  ::hardware_msg::msg::ImuParameters msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hardware_msg::msg::ImuParameters>()
{
  return hardware_msg::msg::builder::Init_ImuParameters_acc_calibrate();
}

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__BUILDER_HPP_
