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
      0x51, 0x22, 0xf4, 0x82, 0x9e, 0x9b, 0x54, 0x48,
      0xbe, 0x0b, 0x5a, 0x0c, 0xa9, 0x5a, 0x49, 0xee,
      0xeb, 0xb3, 0x24, 0x59, 0x1c, 0x35, 0xae, 0x4e,
      0x3b, 0xdd, 0xbb, 0x17, 0x33, 0xce, 0x06, 0xf2,
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
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsCommands__FIELD_NAME__target_vel, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsCommands__FIELD_NAME__target_trq, 10, 10},
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
  "float32 target_pos\n"
  "float32 target_vel\n"
  "float32 target_trq";

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
    {toplevel_type_raw_source, 57, 57},
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
