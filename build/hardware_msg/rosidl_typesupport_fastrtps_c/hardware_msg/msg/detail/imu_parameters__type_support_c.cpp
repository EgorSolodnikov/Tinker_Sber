// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice
#include "hardware_msg/msg/detail/imu_parameters__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "hardware_msg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "hardware_msg/msg/detail/imu_parameters__struct.h"
#include "hardware_msg/msg/detail/imu_parameters__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _ImuParameters__ros_msg_type = hardware_msg__msg__ImuParameters;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
bool cdr_serialize_hardware_msg__msg__ImuParameters(
  const hardware_msg__msg__ImuParameters * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: acc_calibrate
  {
    cdr << (ros_message->acc_calibrate ? true : false);
  }

  // Field name: mag_calibrate
  {
    cdr << (ros_message->mag_calibrate ? true : false);
  }

  // Field name: gyro_calibrate
  {
    cdr << (ros_message->gyro_calibrate ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
bool cdr_deserialize_hardware_msg__msg__ImuParameters(
  eprosima::fastcdr::Cdr & cdr,
  hardware_msg__msg__ImuParameters * ros_message)
{
  // Field name: acc_calibrate
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->acc_calibrate = tmp ? true : false;
  }

  // Field name: mag_calibrate
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->mag_calibrate = tmp ? true : false;
  }

  // Field name: gyro_calibrate
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->gyro_calibrate = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t get_serialized_size_hardware_msg__msg__ImuParameters(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ImuParameters__ros_msg_type * ros_message = static_cast<const _ImuParameters__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: acc_calibrate
  {
    size_t item_size = sizeof(ros_message->acc_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mag_calibrate
  {
    size_t item_size = sizeof(ros_message->mag_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: gyro_calibrate
  {
    size_t item_size = sizeof(ros_message->gyro_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t max_serialized_size_hardware_msg__msg__ImuParameters(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: acc_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: mag_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: gyro_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = hardware_msg__msg__ImuParameters;
    is_plain =
      (
      offsetof(DataType, gyro_calibrate) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
bool cdr_serialize_key_hardware_msg__msg__ImuParameters(
  const hardware_msg__msg__ImuParameters * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: acc_calibrate
  {
    cdr << (ros_message->acc_calibrate ? true : false);
  }

  // Field name: mag_calibrate
  {
    cdr << (ros_message->mag_calibrate ? true : false);
  }

  // Field name: gyro_calibrate
  {
    cdr << (ros_message->gyro_calibrate ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t get_serialized_size_key_hardware_msg__msg__ImuParameters(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ImuParameters__ros_msg_type * ros_message = static_cast<const _ImuParameters__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: acc_calibrate
  {
    size_t item_size = sizeof(ros_message->acc_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mag_calibrate
  {
    size_t item_size = sizeof(ros_message->mag_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: gyro_calibrate
  {
    size_t item_size = sizeof(ros_message->gyro_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_hardware_msg
size_t max_serialized_size_key_hardware_msg__msg__ImuParameters(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: acc_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: mag_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: gyro_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = hardware_msg__msg__ImuParameters;
    is_plain =
      (
      offsetof(DataType, gyro_calibrate) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _ImuParameters__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const hardware_msg__msg__ImuParameters * ros_message = static_cast<const hardware_msg__msg__ImuParameters *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_hardware_msg__msg__ImuParameters(ros_message, cdr);
}

static bool _ImuParameters__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  hardware_msg__msg__ImuParameters * ros_message = static_cast<hardware_msg__msg__ImuParameters *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_hardware_msg__msg__ImuParameters(cdr, ros_message);
}

static uint32_t _ImuParameters__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_hardware_msg__msg__ImuParameters(
      untyped_ros_message, 0));
}

static size_t _ImuParameters__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_hardware_msg__msg__ImuParameters(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ImuParameters = {
  "hardware_msg::msg",
  "ImuParameters",
  _ImuParameters__cdr_serialize,
  _ImuParameters__cdr_deserialize,
  _ImuParameters__get_serialized_size,
  _ImuParameters__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _ImuParameters__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ImuParameters,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__ImuParameters__get_type_hash,
  &hardware_msg__msg__ImuParameters__get_type_description,
  &hardware_msg__msg__ImuParameters__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, hardware_msg, msg, ImuParameters)() {
  return &_ImuParameters__type_support;
}

#if defined(__cplusplus)
}
#endif
