// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hardware_msg:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorData in the package hardware_msg.
typedef struct hardware_msg__msg__MotorData
{
  uint8_t id;
  bool connect;
  bool motor_connected;
  bool ready;
} hardware_msg__msg__MotorData;

// Struct for a sequence of hardware_msg__msg__MotorData.
typedef struct hardware_msg__msg__MotorData__Sequence
{
  hardware_msg__msg__MotorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hardware_msg__msg__MotorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_DATA__STRUCT_H_
