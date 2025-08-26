// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hardware_msg/msg/detail/imu_parameters__rosidl_typesupport_introspection_c.h"
#include "hardware_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hardware_msg/msg/detail/imu_parameters__functions.h"
#include "hardware_msg/msg/detail/imu_parameters__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hardware_msg__msg__ImuParameters__init(message_memory);
}

void hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_fini_function(void * message_memory)
{
  hardware_msg__msg__ImuParameters__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_member_array[3] = {
  {
    "acc_calibrate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__ImuParameters, acc_calibrate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "msg_calibrate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__ImuParameters, msg_calibrate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gyro_calibrate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hardware_msg__msg__ImuParameters, gyro_calibrate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_members = {
  "hardware_msg__msg",  // message namespace
  "ImuParameters",  // message name
  3,  // number of fields
  sizeof(hardware_msg__msg__ImuParameters),
  hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_member_array,  // message members
  hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_init_function,  // function to initialize message memory (memory has to be allocated)
  hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_type_support_handle = {
  0,
  &hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hardware_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hardware_msg, msg, ImuParameters)() {
  if (!hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_type_support_handle.typesupport_identifier) {
    hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &hardware_msg__msg__ImuParameters__rosidl_typesupport_introspection_c__ImuParameters_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
