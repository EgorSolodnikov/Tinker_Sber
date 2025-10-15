// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice
#ifndef HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "hardware_msg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hardware_msg/msg/detail/board_parameters__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
bool cdr_serialize_hardware_msg__msg__BoardParameters(
  const hardware_msg__msg__BoardParameters * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
bool cdr_deserialize_hardware_msg__msg__BoardParameters(
  eprosima::fastcdr::Cdr &,
  hardware_msg__msg__BoardParameters * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t get_serialized_size_hardware_msg__msg__BoardParameters(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t max_serialized_size_hardware_msg__msg__BoardParameters(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
bool cdr_serialize_key_hardware_msg__msg__BoardParameters(
  const hardware_msg__msg__BoardParameters * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t get_serialized_size_key_hardware_msg__msg__BoardParameters(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t max_serialized_size_key_hardware_msg__msg__BoardParameters(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hardware_msg, msg, BoardParameters)();

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
