// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from hardware_msg:msg/MotorsCommands.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "hardware_msg/msg/detail/motors_commands__functions.h"
#include "hardware_msg/msg/detail/motors_commands__struct.hpp"
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

void MotorsCommands_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) hardware_msg::msg::MotorsCommands(_init);
}

void MotorsCommands_fini_function(void * message_memory)
{
  auto typed_message = static_cast<hardware_msg::msg::MotorsCommands *>(message_memory);
  typed_message->~MotorsCommands();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MotorsCommands_message_member_array[3] = {
  {
    "target_pos",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::MotorsCommands, target_pos),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "target_vel",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::MotorsCommands, target_vel),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "target_trq",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::MotorsCommands, target_trq),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MotorsCommands_message_members = {
  "hardware_msg::msg",  // message namespace
  "MotorsCommands",  // message name
  3,  // number of fields
  sizeof(hardware_msg::msg::MotorsCommands),
  false,  // has_any_key_member_
  MotorsCommands_message_member_array,  // message members
  MotorsCommands_init_function,  // function to initialize message memory (memory has to be allocated)
  MotorsCommands_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MotorsCommands_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MotorsCommands_message_members,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__MotorsCommands__get_type_hash,
  &hardware_msg__msg__MotorsCommands__get_type_description,
  &hardware_msg__msg__MotorsCommands__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace hardware_msg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<hardware_msg::msg::MotorsCommands>()
{
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::MotorsCommands_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, hardware_msg, msg, MotorsCommands)() {
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::MotorsCommands_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
