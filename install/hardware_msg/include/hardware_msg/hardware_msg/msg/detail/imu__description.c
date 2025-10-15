// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/Imu.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/imu__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__Imu__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x97, 0x5b, 0xb0, 0x30, 0xd6, 0x04, 0x8d, 0x0b,
      0xfa, 0x41, 0x62, 0x55, 0xac, 0xc0, 0x08, 0x70,
      0x4d, 0x6e, 0x5f, 0x84, 0x22, 0x71, 0xa1, 0x7e,
      0x03, 0xc8, 0x5a, 0x9b, 0xc3, 0xe4, 0xb9, 0x17,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__Imu__TYPE_NAME[] = "hardware_msg/msg/Imu";

// Define type names, field names, and default values
static char hardware_msg__msg__Imu__FIELD_NAME__pitch[] = "pitch";
static char hardware_msg__msg__Imu__FIELD_NAME__roll[] = "roll";
static char hardware_msg__msg__Imu__FIELD_NAME__yaw[] = "yaw";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__Imu__FIELDS[] = {
  {
    {hardware_msg__msg__Imu__FIELD_NAME__pitch, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__Imu__FIELD_NAME__roll, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__Imu__FIELD_NAME__yaw, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
hardware_msg__msg__Imu__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__Imu__TYPE_NAME, 20, 20},
      {hardware_msg__msg__Imu__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 pitch\n"
  "float32 roll\n"
  "float32 yaw";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__Imu__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__Imu__TYPE_NAME, 20, 20},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 39, 39},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__Imu__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__Imu__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
