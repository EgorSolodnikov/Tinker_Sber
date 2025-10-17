// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/MotorsCommands.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/motors_commands__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__MotorsCommands__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb3, 0xea, 0xb2, 0xe0, 0xad, 0xf0, 0xab, 0x17,
      0xb6, 0x1b, 0x10, 0x65, 0x31, 0xd6, 0xc2, 0xc3,
      0xee, 0x83, 0x78, 0x17, 0x77, 0x16, 0xb1, 0xff,
      0xf7, 0xfe, 0x6d, 0x4b, 0x77, 0xa8, 0xc0, 0xd5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__MotorsCommands__TYPE_NAME[] = "hardware_msg/msg/MotorsCommands";

// Define type names, field names, and default values
static char hardware_msg__msg__MotorsCommands__FIELD_NAME__target_pos[] = "target_pos";
static char hardware_msg__msg__MotorsCommands__FIELD_NAME__target_vel[] = "target_vel";
static char hardware_msg__msg__MotorsCommands__FIELD_NAME__target_trq[] = "target_trq";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__MotorsCommands__FIELDS[] = {
  {
    {hardware_msg__msg__MotorsCommands__FIELD_NAME__target_pos, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      10,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsCommands__FIELD_NAME__target_vel, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      10,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsCommands__FIELD_NAME__target_trq, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      10,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
hardware_msg__msg__MotorsCommands__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__MotorsCommands__TYPE_NAME, 31, 31},
      {hardware_msg__msg__MotorsCommands__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32[10] target_pos\n"
  "float32[10] target_vel\n"
  "float32[10] target_trq";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__MotorsCommands__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__MotorsCommands__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 68, 68},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__MotorsCommands__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__MotorsCommands__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
