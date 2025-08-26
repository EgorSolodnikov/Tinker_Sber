// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hardware_msg:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hardware_msg__msg__MotorData __attribute__((deprecated))
#else
# define DEPRECATED__hardware_msg__msg__MotorData __declspec(deprecated)
#endif

namespace hardware_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorData_
{
  using Type = MotorData_<ContainerAllocator>;

  explicit MotorData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->connect = false;
      this->motor_connected = false;
      this->ready = false;
    }
  }

  explicit MotorData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->connect = false;
      this->motor_connected = false;
      this->ready = false;
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _connect_type =
    bool;
  _connect_type connect;
  using _motor_connected_type =
    bool;
  _motor_connected_type motor_connected;
  using _ready_type =
    bool;
  _ready_type ready;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__connect(
    const bool & _arg)
  {
    this->connect = _arg;
    return *this;
  }
  Type & set__motor_connected(
    const bool & _arg)
  {
    this->motor_connected = _arg;
    return *this;
  }
  Type & set__ready(
    const bool & _arg)
  {
    this->ready = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hardware_msg::msg::MotorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const hardware_msg::msg::MotorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hardware_msg::msg::MotorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::MotorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::MotorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hardware_msg::msg::MotorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hardware_msg__msg__MotorData
    std::shared_ptr<hardware_msg::msg::MotorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hardware_msg__msg__MotorData
    std::shared_ptr<hardware_msg::msg::MotorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorData_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->connect != other.connect) {
      return false;
    }
    if (this->motor_connected != other.motor_connected) {
      return false;
    }
    if (this->ready != other.ready) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorData_

// alias to use template instance with default allocator
using MotorData =
  hardware_msg::msg::MotorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_
