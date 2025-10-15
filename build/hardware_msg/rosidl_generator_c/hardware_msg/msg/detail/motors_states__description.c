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
      0xca, 0x3c, 0x7f, 0x13, 0x12, 0x1f, 0x1d, 0x5e,
      0x23, 0x80, 0x18, 0xd2, 0x04, 0xb3, 0x83, 0x15,
      0x67, 0x1a, 0x36, 0xad, 0x63, 0x33, 0x3b, 0xa4,
      0xed, 0xa1, 0xb3, 0xce, 0xac, 0xda, 0x96, 0x30,
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
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsStates__FIELD_NAME__current_vel, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorsStates__FIELD_NAME__current_trq, 11, 11},
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
  "float32 current_pos\n"
  "float32 current_vel\n"
  "float32 current_trq";

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
    {toplevel_type_raw_source, 60, 60},
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
