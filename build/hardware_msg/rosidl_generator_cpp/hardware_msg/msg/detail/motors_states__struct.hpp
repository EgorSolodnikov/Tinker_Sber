// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hardware_msg:msg/MotorsStates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/motors_states.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__STRUCT_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hardware_msg__msg__MotorsStates __attribute__((deprecated))
#else
# define DEPRECATED__hardware_msg__msg__MotorsStates __declspec(deprecated)
#endif

namespace hardware_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorsStates_
{
  using Type = MotorsStates_<ContainerAllocator>;

  explicit MotorsStates_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 10>::iterator, float>(this->current_pos.begin(), this->current_pos.end(), 0.0f);
      std::fill<typename std::array<float, 10>::iterator, float>(this->current_vel.begin(), this->current_vel.end(), 0.0f);
      std::fill<typename std::array<float, 10>::iterator, float>(this->current_trq.begin(), this->current_trq.end(), 0.0f);
    }
  }

  explicit MotorsStates_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : current_pos(_alloc),
    current_vel(_alloc),
    current_trq(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 10>::iterator, float>(this->current_pos.begin(), this->current_pos.end(), 0.0f);
      std::fill<typename std::array<float, 10>::iterator, float>(this->current_vel.begin(), this->current_vel.end(), 0.0f);
      std::fill<typename std::array<float, 10>::iterator, float>(this->current_trq.begin(), this->current_trq.end(), 0.0f);
    }
  }

  // field types and members
  using _current_pos_type =
    std::array<float, 10>;
  _current_pos_type current_pos;
  using _current_vel_type =
    std::array<float, 10>;
  _current_vel_type current_vel;
  using _current_trq_type =
    std::array<float, 10>;
  _current_trq_type current_trq;

  // setters for named parameter idiom
  Type & set__current_pos(
    const std::array<float, 10> & _arg)
  {
    this->current_pos = _arg;
    return *this;
  }
  Type & set__current_vel(
    const std::array<float, 10> & _arg)
  {
    this->current_vel = _arg;
    return *this;
  }
  Type & set__current_trq(
    const std::array<float, 10> & _arg)
  {
    this->current_trq = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hardware_msg::msg::MotorsStates_<ContainerAllocator> *;
  using ConstRawPtr =
    const hardware_msg::msg::MotorsStates_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorsStates_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorsStates_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hardware_msg__msg__MotorsStates
    std::shared_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hardware_msg__msg__MotorsStates
    std::shared_ptr<hardware_msg::msg::MotorsStates_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorsStates_ & other) const
  {
    if (this->current_pos != other.current_pos) {
      return false;
    }
    if (this->current_vel != other.current_vel) {
      return false;
    }
    if (this->current_trq != other.current_trq) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorsStates_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorsStates_

// alias to use template instance with default allocator
using MotorsStates =
  hardware_msg::msg::MotorsStates_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTORS_STATES__STRUCT_HPP_
