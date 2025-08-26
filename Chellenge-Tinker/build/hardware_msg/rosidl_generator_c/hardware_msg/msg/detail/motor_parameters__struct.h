// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hardware_msg:msg/MotorParameters.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__STRUCT_H_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorParameters in the package hardware_msg.
typedef struct hardware_msg__msg__MotorParameters
{
  bool enable;
  bool reset_zero;
  bool reset_error;
  float kp;
  float kd;
} hardware_msg__msg__MotorParameters;

// Struct for a sequence of hardware_msg__msg__MotorParameters.
typedef struct hardware_msg__msg__MotorParameters__Sequence
{
  hardware_msg__msg__MotorParameters * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hardware_msg__msg__MotorParameters__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__STRUCT_H_
