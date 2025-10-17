// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hardware_msg:msg/MotorsCommands.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hardware_msg/msg/detail/motors_commands__rosidl_typesupport_introspection_c.h"
#include "hardware_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hardware_msg/msg/detail/motors_commands__functions.h"
#include "hardware_msg/msg/detail/motors_commands__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hardware_msg__msg__MotorsCommands__init(message_memory);
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_fini_function(void * message_memory)
{
  hardware_msg__msg__MotorsCommands__fini(message_memory);
}

size_t hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__size_function__MotorsCommands__target_pos(
  const void * untyped_member)
{
  (void)untyped_member;
  return 10;
}

const void * hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_pos(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_pos(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__fetch_function__MotorsCommands__target_pos(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_pos(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__assign_function__MotorsCommands__target_pos(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_pos(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__size_function__MotorsCommands__target_vel(
  const void * untyped_member)
{
  (void)untyped_member;
  return 10;
}

const void * hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_vel(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_vel(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__fetch_function__MotorsCommands__target_vel(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_vel(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__assign_function__MotorsCommands__target_vel(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_vel(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

size_t hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__size_function__MotorsCommands__target_trq(
  const void * untyped_member)
{
  (void)untyped_member;
  return 10;
}

const void * hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_trq(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_trq(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__fetch_function__MotorsCommands__target_trq(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_trq(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__assign_function__MotorsCommands__target_trq(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_trq(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_member_array[3] = {
  {
    "target_pos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    10,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__MotorsCommands, target_pos),  // bytes offset in struct
    NULL,  // default value
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__size_function__MotorsCommands__target_pos,  // size() function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_pos,  // get_const(index) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_pos,  // get(index) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__fetch_function__MotorsCommands__target_pos,  // fetch(index, &value) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__assign_function__MotorsCommands__target_pos,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    10,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__MotorsCommands, target_vel),  // bytes offset in struct
    NULL,  // default value
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__size_function__MotorsCommands__target_vel,  // size() function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_vel,  // get_const(index) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_vel,  // get(index) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__fetch_function__MotorsCommands__target_vel,  // fetch(index, &value) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__assign_function__MotorsCommands__target_vel,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_trq",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    10,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__MotorsCommands, target_trq),  // bytes offset in struct
    NULL,  // default value
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__size_function__MotorsCommands__target_trq,  // size() function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_const_function__MotorsCommands__target_trq,  // get_const(index) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__get_function__MotorsCommands__target_trq,  // get(index) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__fetch_function__MotorsCommands__target_trq,  // fetch(index, &value) function pointer
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__assign_function__MotorsCommands__target_trq,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_members = {
  "hardware_msg__msg",  // message namespace
  "MotorsCommands",  // message name
  3,  // number of fields
  sizeof(hardware_msg__msg__MotorsCommands),
  false,  // has_any_key_member_
  hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_member_array,  // message members
  hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_init_function,  // function to initialize message memory (memory has to be allocated)
  hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_type_support_handle = {
  0,
  &hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_members,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__MotorsCommands__get_type_hash,
  &hardware_msg__msg__MotorsCommands__get_type_description,
  &hardware_msg__msg__MotorsCommands__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hardware_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hardware_msg, msg, MotorsCommands)() {
  if (!hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_type_support_handle.typesupport_identifier) {
    hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hardware_msg__msg__MotorsCommands__rosidl_typesupport_introspection_c__MotorsCommands_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
