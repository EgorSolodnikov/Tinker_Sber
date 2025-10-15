// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hardware_msg:msg/Imu.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/imu.h"


#ifndef HARDWARE_MSG__MSG__DETAIL__IMU__STRUCT_H_
#define HARDWARE_MSG__MSG__DETAIL__IMU__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Imu in the package hardware_msg.
typedef struct hardware_msg__msg__Imu
{
  float pitch;
  float roll;
  float yaw;
} hardware_msg__msg__Imu;

// Struct for a sequence of hardware_msg__msg__Imu.
typedef struct hardware_msg__msg__Imu__Sequence
{
  hardware_msg__msg__Imu * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hardware_msg__msg__Imu__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU__STRUCT_H_
