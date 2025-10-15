// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/MotorData.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/motor_data__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__MotorData__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x0b, 0x0e, 0x17, 0x15, 0xb8, 0x6a, 0x82, 0x2b,
      0x49, 0x1d, 0xbe, 0x18, 0x88, 0x12, 0x06, 0x02,
      0x2a, 0xa1, 0xa0, 0xd3, 0x54, 0xc9, 0x0b, 0x25,
      0x2a, 0x73, 0xdf, 0xe7, 0x7a, 0x2f, 0x45, 0x14,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__MotorData__TYPE_NAME[] = "hardware_msg/msg/MotorData";

// Define type names, field names, and default values
static char hardware_msg__msg__MotorData__FIELD_NAME__id[] = "id";
static char hardware_msg__msg__MotorData__FIELD_NAME__connect[] = "connect";
static char hardware_msg__msg__MotorData__FIELD_NAME__motor_connected[] = "motor_connected";
static char hardware_msg__msg__MotorData__FIELD_NAME__ready[] = "ready";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__MotorData__FIELDS[] = {
  {
    {hardware_msg__msg__MotorData__FIELD_NAME__id, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorData__FIELD_NAME__connect, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorData__FIELD_NAME__motor_connected, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorData__FIELD_NAME__ready, 5, 5},
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
hardware_msg__msg__MotorData__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__MotorData__TYPE_NAME, 26, 26},
      {hardware_msg__msg__MotorData__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 id\n"
  "bool connect\n"
  "bool motor_connected\n"
  "bool ready";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__MotorData__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__MotorData__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 54, 54},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__MotorData__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__MotorData__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
