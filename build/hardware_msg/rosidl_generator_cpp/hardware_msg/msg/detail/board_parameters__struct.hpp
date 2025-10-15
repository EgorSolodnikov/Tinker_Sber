// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/board_parameters.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__STRUCT_HPP_
#define HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hardware_msg__msg__BoardParameters __attribute__((deprecated))
#else
# define DEPRECATED__hardware_msg__msg__BoardParameters __declspec(deprecated)
#endif

namespace hardware_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BoardParameters_
{
  using Type = BoardParameters_<ContainerAllocator>;

  explicit BoardParameters_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->beep_state = 0.0f;
    }
  }

  explicit BoardParameters_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->beep_state = 0.0f;
    }
  }

  // field types and members
  using _beep_state_type =
    float;
  _beep_state_type beep_state;

  // setters for named parameter idiom
  Type & set__beep_state(
    const float & _arg)
  {
    this->beep_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hardware_msg::msg::BoardParameters_<ContainerAllocator> *;
  using ConstRawPtr =
    const hardware_msg::msg::BoardParameters_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::BoardParameters_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::BoardParameters_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hardware_msg__msg__BoardParameters
    std::shared_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hardware_msg__msg__BoardParameters
    std::shared_ptr<hardware_msg::msg::BoardParameters_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BoardParameters_ & other) const
  {
    if (this->beep_state != other.beep_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const BoardParameters_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BoardParameters_

// alias to use template instance with default allocator
using BoardParameters =
  hardware_msg::msg::BoardParameters_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__STRUCT_HPP_
