// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hardware_msg:msg/MotorsCommands.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__STRUCT_H_
#define HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorsCommands in the package hardware_msg.
typedef struct hardware_msg__msg__MotorsCommands
{
  float target_pos;
  float target_vel;
  float target_trq;
} hardware_msg__msg__MotorsCommands;

// Struct for a sequence of hardware_msg__msg__MotorsCommands.
typedef struct hardware_msg__msg__MotorsCommands__Sequence
{
  hardware_msg__msg__MotorsCommands * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hardware_msg__msg__MotorsCommands__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTORS_COMMANDS__STRUCT_H_
