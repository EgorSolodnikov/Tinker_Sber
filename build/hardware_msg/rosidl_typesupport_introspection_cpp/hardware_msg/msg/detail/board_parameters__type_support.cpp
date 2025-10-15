// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "hardware_msg/msg/detail/board_parameters__functions.h"
#include "hardware_msg/msg/detail/board_parameters__struct.hpp"
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

void BoardParameters_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) hardware_msg::msg::BoardParameters(_init);
}

void BoardParameters_fini_function(void * message_memory)
{
  auto typed_message = static_cast<hardware_msg::msg::BoardParameters *>(message_memory);
  typed_message->~BoardParameters();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember BoardParameters_message_member_array[1] = {
  {
    "beep_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::BoardParameters, beep_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers BoardParameters_message_members = {
  "hardware_msg::msg",  // message namespace
  "BoardParameters",  // message name
  1,  // number of fields
  sizeof(hardware_msg::msg::BoardParameters),
  false,  // has_any_key_member_
  BoardParameters_message_member_array,  // message members
  BoardParameters_init_function,  // function to initialize message memory (memory has to be allocated)
  BoardParameters_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t BoardParameters_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &BoardParameters_message_members,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__BoardParameters__get_type_hash,
  &hardware_msg__msg__BoardParameters__get_type_description,
  &hardware_msg__msg__BoardParameters__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace hardware_msg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<hardware_msg::msg::BoardParameters>()
{
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::BoardParameters_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, hardware_msg, msg, BoardParameters)() {
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::BoardParameters_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
