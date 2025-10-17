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
      0xcb, 0xec, 0xb0, 0x57, 0xb4, 0x75, 0xe5, 0x3b,
      0xed, 0x2b, 0x75, 0x77, 0x41, 0x77, 0x03, 0xb7,
      0xc5, 0x73, 0xcd, 0x05, 0x72, 0x38, 0x70, 0xce,
      0x2a, 0x7e, 0x90, 0x7d, 0x02, 0x26, 0x1e, 0x6d,
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
static char hardware_msg__msg__ImuParameters__FIELD_NAME__mag_calibrate[] = "mag_calibrate";
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
    {hardware_msg__msg__ImuParameters__FIELD_NAME__mag_calibrate, 13, 13},
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
  "bool mag_calibrate\n"
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
    {toplevel_type_raw_source, 57, 57},
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
