// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "hardware_msg/msg/detail/imu_parameters__functions.h"
#include "hardware_msg/msg/detail/imu_parameters__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace hardware_msg
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ImuParameters_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) hardware_msg::msg::ImuParameters(_init);
}

void ImuParameters_fini_function(void * message_memory)
{
  auto typed_message = static_cast<hardware_msg::msg::ImuParameters *>(message_memory);
  typed_message->~ImuParameters();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ImuParameters_message_member_array[3] = {
  {
    "acc_calibrate",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::ImuParameters, acc_calibrate),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "mag_calibrate",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::ImuParameters, mag_calibrate),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "gyro_calibrate",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::ImuParameters, gyro_calibrate),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ImuParameters_message_members = {
  "hardware_msg::msg",  // message namespace
  "ImuParameters",  // message name
  3,  // number of fields
  sizeof(hardware_msg::msg::ImuParameters),
  false,  // has_any_key_member_
  ImuParameters_message_member_array,  // message members
  ImuParameters_init_function,  // function to initialize message memory (memory has to be allocated)
  ImuParameters_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ImuParameters_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ImuParameters_message_members,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__ImuParameters__get_type_hash,
  &hardware_msg__msg__ImuParameters__get_type_description,
  &hardware_msg__msg__ImuParameters__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace hardware_msg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<hardware_msg::msg::ImuParameters>()
{
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::ImuParameters_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, hardware_msg, msg, ImuParameters)() {
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::ImuParameters_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
