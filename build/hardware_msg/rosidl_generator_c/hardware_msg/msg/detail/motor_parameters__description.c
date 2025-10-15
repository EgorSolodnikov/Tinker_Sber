// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from hardware_msg:msg/MotorParameters.idl
// generated code does not contain a copyright notice

#include "hardware_msg/msg/detail/motor_parameters__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__MotorParameters__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2f, 0x28, 0x74, 0xa9, 0x19, 0xbc, 0x63, 0xcc,
      0xda, 0xed, 0xfb, 0xb5, 0x43, 0xb9, 0xe1, 0x4e,
      0x9f, 0xc3, 0x55, 0xa9, 0xc8, 0x34, 0x56, 0x6d,
      0xe2, 0xea, 0xc5, 0xad, 0x36, 0xde, 0x97, 0x94,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char hardware_msg__msg__MotorParameters__TYPE_NAME[] = "hardware_msg/msg/MotorParameters";

// Define type names, field names, and default values
static char hardware_msg__msg__MotorParameters__FIELD_NAME__enable[] = "enable";
static char hardware_msg__msg__MotorParameters__FIELD_NAME__reset_zero[] = "reset_zero";
static char hardware_msg__msg__MotorParameters__FIELD_NAME__reset_error[] = "reset_error";
static char hardware_msg__msg__MotorParameters__FIELD_NAME__kp[] = "kp";
static char hardware_msg__msg__MotorParameters__FIELD_NAME__kd[] = "kd";

static rosidl_runtime_c__type_description__Field hardware_msg__msg__MotorParameters__FIELDS[] = {
  {
    {hardware_msg__msg__MotorParameters__FIELD_NAME__enable, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorParameters__FIELD_NAME__reset_zero, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorParameters__FIELD_NAME__reset_error, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorParameters__FIELD_NAME__kp, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {hardware_msg__msg__MotorParameters__FIELD_NAME__kd, 2, 2},
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
hardware_msg__msg__MotorParameters__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {hardware_msg__msg__MotorParameters__TYPE_NAME, 32, 32},
      {hardware_msg__msg__MotorParameters__FIELDS, 5, 5},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool enable\n"
  "bool reset_zero\n"
  "bool reset_error\n"
  "float32 kp\n"
  "float32 kd";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__MotorParameters__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {hardware_msg__msg__MotorParameters__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 67, 67},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__MotorParameters__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *hardware_msg__msg__MotorParameters__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
