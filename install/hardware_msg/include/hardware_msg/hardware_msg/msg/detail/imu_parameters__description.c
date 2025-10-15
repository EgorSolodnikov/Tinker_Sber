// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/imu_parameters__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__ImuParameters__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd7, 0x89, 0x3e, 0x46, 0x5b, 0x13, 0xf0, 0x7c,
      0x62, 0xd9, 0xc4, 0x20, 0x42, 0xe3, 0xc2, 0x3d,
      0x33, 0x97, 0xe2, 0x74, 0x25, 0x8d, 0x24, 0xd3,
      0x83, 0x50, 0x65, 0x1a, 0x19, 0x53, 0x3e, 0x9a,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__ImuParameters__TYPE_NAME[] = "hardware_msg/msg/ImuParameters";

// Define type names, field names, and default values
static char hardware_msg__msg__ImuParameters__FIELD_NAME__acc_calibrate[] = "acc_calibrate";
static char hardware_msg__msg__ImuParameters__FIELD_NAME__msg_calibrate[] = "msg_calibrate";
static char hardware_msg__msg__ImuParameters__FIELD_NAME__gyro_calibrate[] = "gyro_calibrate";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__ImuParameters__FIELDS[] = {
  {
    {hardware_msg__msg__ImuParameters__FIELD_NAME__acc_calibrate, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__ImuParameters__FIELD_NAME__msg_calibrate, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__ImuParameters__FIELD_NAME__gyro_calibrate, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
hardware_msg__msg__ImuParameters__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__ImuParameters__TYPE_NAME, 30, 30},
      {hardware_msg__msg__ImuParameters__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool acc_calibrate\n"
  "bool msg_calibrate\n"
  "bool gyro_calibrate";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__ImuParameters__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__ImuParameters__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 58, 58},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__ImuParameters__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__ImuParameters__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
