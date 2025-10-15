// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/BoardParameters.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/board_parameters__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__BoardParameters__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xcf, 0xe9, 0x40, 0x7a, 0x51, 0x22, 0x84, 0x24,
      0xa3, 0x61, 0xd4, 0x9d, 0x28, 0x5a, 0xa6, 0xe7,
      0x90, 0x2a, 0x25, 0x55, 0x66, 0x6b, 0x26, 0x98,
      0x5f, 0x4f, 0x62, 0xd8, 0x1c, 0xd9, 0xf7, 0x9b,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__BoardParameters__TYPE_NAME[] = "hardware_msg/msg/BoardParameters";

// Define type names, field names, and default values
static char hardware_msg__msg__BoardParameters__FIELD_NAME__beep_state[] = "beep_state";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__BoardParameters__FIELDS[] = {
  {
    {hardware_msg__msg__BoardParameters__FIELD_NAME__beep_state, 10, 10},
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
hardware_msg__msg__BoardParameters__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__BoardParameters__TYPE_NAME, 32, 32},
      {hardware_msg__msg__BoardParameters__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 beep_state";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__BoardParameters__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__BoardParameters__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 19, 19},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__BoardParameters__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__BoardParameters__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
