// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/board_parameters.h"


#ifndef HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__STRUCT_H_
#define HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/BoardParameters in the package hardware_msg.
typedef struct hardware_msg__msg__BoardParameters
{
  float beep_state;
} hardware_msg__msg__BoardParameters;

// Struct for a sequence of hardware_msg__msg__BoardParameters.
typedef struct hardware_msg__msg__BoardParameters__Sequence
{
  hardware_msg__msg__BoardParameters * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hardware_msg__msg__BoardParameters__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__BOARD_PARAMETERS__STRUCT_H_
