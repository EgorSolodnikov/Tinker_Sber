// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hardware_msg:msg/MotorsCommands.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motors_commands.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__STRUCT_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hardware_msg__msg__MotorsCommands __attribute__((deprecated))
#else
# define DEPRECATED__hardware_msg__msg__MotorsCommands __declspec(deprecated)
#endif

namespace hardware_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorsCommands_
{
  using Type = MotorsCommands_<ContainerAllocator>;

  explicit MotorsCommands_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_pos = 0.0f;
      this->target_vel = 0.0f;
      this->target_trq = 0.0f;
    }
  }

  explicit MotorsCommands_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_pos = 0.0f;
      this->target_vel = 0.0f;
      this->target_trq = 0.0f;
    }
  }

  // field types and members
  using _target_pos_type =
    float;
  _target_pos_type target_pos;
  using _target_vel_type =
    float;
  _target_vel_type target_vel;
  using _target_trq_type =
    float;
  _target_trq_type target_trq;

  // setters for named parameter idiom
  Type & set__target_pos(
    const float & _arg)
  {
    this->target_pos = _arg;
    return *this;
  }
  Type & set__target_vel(
    const float & _arg)
  {
    this->target_vel = _arg;
    return *this;
  }
  Type & set__target_trq(
    const float & _arg)
  {
    this->target_trq = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hardware_msg::msg::MotorsCommands_<ContainerAllocator> *;
  using ConstRawPtr =
    const hardware_msg::msg::MotorsCommands_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorsCommands_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorsCommands_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hardware_msg__msg__MotorsCommands
    std::shared_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hardware_msg__msg__MotorsCommands
    std::shared_ptr<hardware_msg::msg::MotorsCommands_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorsCommands_ & other) const
  {
    if (this->target_pos != other.target_pos) {
      return false;
    }
    if (this->target_vel != other.target_vel) {
      return false;
    }
    if (this->target_trq != other.target_trq) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorsCommands_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorsCommands_

// alias to use template instance with default allocator
using MotorsCommands =
  hardware_msg::msg::MotorsCommands_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__STRUCT_HPP_
