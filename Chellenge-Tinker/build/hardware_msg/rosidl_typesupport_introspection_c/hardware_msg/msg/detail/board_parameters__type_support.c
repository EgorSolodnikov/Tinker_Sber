// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hardware_msg/msg/detail/board_parameters__rosidl_typesupport_introspection_c.h"
#include "hardware_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hardware_msg/msg/detail/board_parameters__functions.h"
#include "hardware_msg/msg/detail/board_parameters__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hardware_msg__msg__BoardParameters__init(message_memory);
}

void hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_fini_function(void * message_memory)
{
  hardware_msg__msg__BoardParameters__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_member_array[1] = {
  {
    "beep_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__BoardParameters, beep_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_members = {
  "hardware_msg__msg",  // message namespace
  "BoardParameters",  // message name
  1,  // number of fields
  sizeof(hardware_msg__msg__BoardParameters),
  false,  // has_any_key_member_
  hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_member_array,  // message members
  hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_init_function,  // function to initialize message memory (memory has to be allocated)
  hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_type_support_handle = {
  0,
  &hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_members,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__BoardParameters__get_type_hash,
  &hardware_msg__msg__BoardParameters__get_type_description,
  &hardware_msg__msg__BoardParameters__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hardware_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hardware_msg, msg, BoardParameters)() {
  if (!hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_type_support_handle.typesupport_identifier) {
    hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hardware_msg__msg__BoardParameters__rosidl_typesupport_introspection_c__BoardParameters_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
