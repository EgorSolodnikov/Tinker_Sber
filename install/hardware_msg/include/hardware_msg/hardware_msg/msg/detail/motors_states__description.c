// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/MotorsStates.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/motors_states__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__MotorsStates__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2c, 0xe6, 0x65, 0xca, 0x88, 0xb8, 0xa6, 0xa8,
      0xa3, 0x4c, 0x6f, 0xa4, 0xea, 0x60, 0xee, 0xc3,
      0x87, 0x3a, 0xbe, 0xd4, 0x1c, 0xf6, 0x0f, 0x46,
      0xaf, 0x08, 0x69, 0x7d, 0x45, 0xe8, 0xda, 0x7e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__MotorsStates__TYPE_NAME[] = "hardware_msg/msg/MotorsStates";

// Define type names, field names, and default values
static char hardware_msg__msg__MotorsStates__FIELD_NAME__current_pos[] = "current_pos";
static char hardware_msg__msg__MotorsStates__FIELD_NAME__current_vel[] = "current_vel";
static char hardware_msg__msg__MotorsStates__FIELD_NAME__current_trq[] = "current_trq";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__MotorsStates__FIELDS[] = {
  {
    {hardware_msg__msg__MotorsStates__FIELD_NAME__current_pos, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      10,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsStates__FIELD_NAME__current_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT_ARRAY,
      10,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsStates__FIELD_NAME__current_trq, 11, 11},
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
hardware_msg__msg__MotorsStates__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__MotorsStates__TYPE_NAME, 29, 29},
      {hardware_msg__msg__MotorsStates__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32[10] current_pos\n"
  "float32[10] current_vel\n"
  "float32[10] current_trq";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__MotorsStates__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__MotorsStates__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 72, 72},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__MotorsStates__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__MotorsStates__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
