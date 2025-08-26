// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hardware_msg:msg/MotorParameters.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__STRUCT_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hardware_msg__msg__MotorParameters __attribute__((deprecated))
#else
# define DEPRECATED__hardware_msg__msg__MotorParameters __declspec(deprecated)
#endif

namespace hardware_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorParameters_
{
  using Type = MotorParameters_<ContainerAllocator>;

  explicit MotorParameters_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enable = false;
      this->reset_zero = false;
      this->reset_error = false;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  explicit MotorParameters_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enable = false;
      this->reset_zero = false;
      this->reset_error = false;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  // field types and members
  using _enable_type =
    bool;
  _enable_type enable;
  using _reset_zero_type =
    bool;
  _reset_zero_type reset_zero;
  using _reset_error_type =
    bool;
  _reset_error_type reset_error;
  using _kp_type =
    float;
  _kp_type kp;
  using _kd_type =
    float;
  _kd_type kd;

  // setters for named parameter idiom
  Type & set__enable(
    const bool & _arg)
  {
    this->enable = _arg;
    return *this;
  }
  Type & set__reset_zero(
    const bool & _arg)
  {
    this->reset_zero = _arg;
    return *this;
  }
  Type & set__reset_error(
    const bool & _arg)
  {
    this->reset_error = _arg;
    return *this;
  }
  Type & set__kp(
    const float & _arg)
  {
    this->kp = _arg;
    return *this;
  }
  Type & set__kd(
    const float & _arg)
  {
    this->kd = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hardware_msg::msg::MotorParameters_<ContainerAllocator> *;
  using ConstRawPtr =
    const hardware_msg::msg::MotorParameters_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorParameters_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorParameters_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hardware_msg__msg__MotorParameters
    std::shared_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hardware_msg__msg__MotorParameters
    std::shared_ptr<hardware_msg::msg::MotorParameters_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorParameters_ & other) const
  {
    if (this->enable != other.enable) {
      return false;
    }
    if (this->reset_zero != other.reset_zero) {
      return false;
    }
    if (this->reset_error != other.reset_error) {
      return false;
    }
    if (this->kp != other.kp) {
      return false;
    }
    if (this->kd != other.kd) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorParameters_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorParameters_

// alias to use template instance with default allocator
using MotorParameters =
  hardware_msg::msg::MotorParameters_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__STRUCT_HPP_
