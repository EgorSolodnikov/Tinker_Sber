// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from hardware_msg:msg/MotorsStates.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "hardware_msg/msg/detail/motors_states__functions.h"
#include "hardware_msg/msg/detail/motors_states__struct.hpp"
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

void MotorsStates_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) hardware_msg::msg::MotorsStates(_init);
}

void MotorsStates_fini_function(void * message_memory)
{
  auto typed_message = static_cast<hardware_msg::msg::MotorsStates *>(message_memory);
  typed_message->~MotorsStates();
}

size_t size_function__MotorsStates__current_pos(const void * untyped_member)
{
  (void)untyped_member;
  return 10;
}

const void * get_const_function__MotorsStates__current_pos(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 10> *>(untyped_member);
  return &member[index];
}

void * get_function__MotorsStates__current_pos(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 10> *>(untyped_member);
  return &member[index];
}

void fetch_function__MotorsStates__current_pos(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MotorsStates__current_pos(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MotorsStates__current_pos(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MotorsStates__current_pos(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__MotorsStates__current_vel(const void * untyped_member)
{
  (void)untyped_member;
  return 10;
}

const void * get_const_function__MotorsStates__current_vel(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 10> *>(untyped_member);
  return &member[index];
}

void * get_function__MotorsStates__current_vel(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 10> *>(untyped_member);
  return &member[index];
}

void fetch_function__MotorsStates__current_vel(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MotorsStates__current_vel(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MotorsStates__current_vel(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MotorsStates__current_vel(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

size_t size_function__MotorsStates__current_trq(const void * untyped_member)
{
  (void)untyped_member;
  return 10;
}

const void * get_const_function__MotorsStates__current_trq(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<float, 10> *>(untyped_member);
  return &member[index];
}

void * get_function__MotorsStates__current_trq(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<float, 10> *>(untyped_member);
  return &member[index];
}

void fetch_function__MotorsStates__current_trq(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MotorsStates__current_trq(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MotorsStates__current_trq(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MotorsStates__current_trq(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MotorsStates_message_member_array[3] = {
  {
    "current_pos",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    10,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::MotorsStates, current_pos),  // bytes offset in struct
    nullptr,  // default value
    size_function__MotorsStates__current_pos,  // size() function pointer
    get_const_function__MotorsStates__current_pos,  // get_const(index) function pointer
    get_function__MotorsStates__current_pos,  // get(index) function pointer
    fetch_function__MotorsStates__current_pos,  // fetch(index, &value) function pointer
    assign_function__MotorsStates__current_pos,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "current_vel",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    10,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::MotorsStates, current_vel),  // bytes offset in struct
    nullptr,  // default value
    size_function__MotorsStates__current_vel,  // size() function pointer
    get_const_function__MotorsStates__current_vel,  // get_const(index) function pointer
    get_function__MotorsStates__current_vel,  // get(index) function pointer
    fetch_function__MotorsStates__current_vel,  // fetch(index, &value) function pointer
    assign_function__MotorsStates__current_vel,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "current_trq",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    10,  // array size
    false,  // is upper bound
    offsetof(hardware_msg::msg::MotorsStates, current_trq),  // bytes offset in struct
    nullptr,  // default value
    size_function__MotorsStates__current_trq,  // size() function pointer
    get_const_function__MotorsStates__current_trq,  // get_const(index) function pointer
    get_function__MotorsStates__current_trq,  // get(index) function pointer
    fetch_function__MotorsStates__current_trq,  // fetch(index, &value) function pointer
    assign_function__MotorsStates__current_trq,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MotorsStates_message_members = {
  "hardware_msg::msg",  // message namespace
  "MotorsStates",  // message name
  3,  // number of fields
  sizeof(hardware_msg::msg::MotorsStates),
  false,  // has_any_key_member_
  MotorsStates_message_member_array,  // message members
  MotorsStates_init_function,  // function to initialize message memory (memory has to be allocated)
  MotorsStates_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MotorsStates_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MotorsStates_message_members,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__MotorsStates__get_type_hash,
  &hardware_msg__msg__MotorsStates__get_type_description,
  &hardware_msg__msg__MotorsStates__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace hardware_msg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<hardware_msg::msg::MotorsStates>()
{
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::MotorsStates_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, hardware_msg, msg, MotorsStates)() {
  return &::hardware_msg::msg::rosidl_typesupport_introspection_cpp::MotorsStates_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
