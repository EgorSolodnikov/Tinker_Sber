// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/imu_parameters.hpp"


#ifndef HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__STRUCT_HPP_
#define HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hardware_msg__msg__ImuParameters __attribute__((deprecated))
#else
# define DEPRECATED__hardware_msg__msg__ImuParameters __declspec(deprecated)
#endif

namespace hardware_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ImuParameters_
{
  using Type = ImuParameters_<ContainerAllocator>;

  explicit ImuParameters_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->acc_calibrate = false;
      this->msg_calibrate = false;
      this->gyro_calibrate = false;
    }
  }

  explicit ImuParameters_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->acc_calibrate = false;
      this->msg_calibrate = false;
      this->gyro_calibrate = false;
    }
  }

  // field types and members
  using _acc_calibrate_type =
    bool;
  _acc_calibrate_type acc_calibrate;
  using _msg_calibrate_type =
    bool;
  _msg_calibrate_type msg_calibrate;
  using _gyro_calibrate_type =
    bool;
  _gyro_calibrate_type gyro_calibrate;

  // setters for named parameter idiom
  Type & set__acc_calibrate(
    const bool & _arg)
  {
    this->acc_calibrate = _arg;
    return *this;
  }
  Type & set__msg_calibrate(
    const bool & _arg)
  {
    this->msg_calibrate = _arg;
    return *this;
  }
  Type & set__gyro_calibrate(
    const bool & _arg)
  {
    this->gyro_calibrate = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hardware_msg::msg::ImuParameters_<ContainerAllocator> *;
  using ConstRawPtr =
    const hardware_msg::msg::ImuParameters_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::ImuParameters_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hardware_msg::msg::ImuParameters_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hardware_msg__msg__ImuParameters
    std::shared_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hardware_msg__msg__ImuParameters
    std::shared_ptr<hardware_msg::msg::ImuParameters_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ImuParameters_ & other) const
  {
    if (this->acc_calibrate != other.acc_calibrate) {
      return false;
    }
    if (this->msg_calibrate != other.msg_calibrate) {
      return false;
    }
    if (this->gyro_calibrate != other.gyro_calibrate) {
      return false;
    }
    return true;
  }
  bool operator!=(const ImuParameters_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ImuParameters_

// alias to use template instance with default allocator
using ImuParameters =
  hardware_msg::msg::ImuParameters_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hardware_msg

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__STRUCT_HPP_
