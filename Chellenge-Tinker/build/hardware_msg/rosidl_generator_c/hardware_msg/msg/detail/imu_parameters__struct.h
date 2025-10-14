// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/imu_parameters.h"


#ifndef HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__STRUCT_H_
#define HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ImuParameters in the package hardware_msg.
typedef struct hardware_msg__msg__ImuParameters
{
  bool acc_calibrate;
  bool msg_calibrate;
  bool gyro_calibrate;
} hardware_msg__msg__ImuParameters;

// Struct for a sequence of hardware_msg__msg__ImuParameters.
typedef struct hardware_msg__msg__ImuParameters__Sequence
{
  hardware_msg__msg__ImuParameters * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hardware_msg__msg__ImuParameters__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__STRUCT_H_
