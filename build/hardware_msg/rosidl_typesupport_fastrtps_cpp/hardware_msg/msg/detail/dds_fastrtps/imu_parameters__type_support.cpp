// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice
#include "hardware_msg/msg/detail/imu_parameters__rosidl_typesupport_fastrtps_cpp.hpp"
#include "hardware_msg/msg/detail/imu_parameters__functions.h"
#include "hardware_msg/msg/detail/imu_parameters__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace hardware_msg
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
cdr_serialize(
  const hardware_msg::msg::ImuParameters & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: acc_calibrate
  cdr << (ros_message.acc_calibrate ? true : false);

  // Member: mag_calibrate
  cdr << (ros_message.mag_calibrate ? true : false);

  // Member: gyro_calibrate
  cdr << (ros_message.gyro_calibrate ? true : false);

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  hardware_msg::msg::ImuParameters & ros_message)
{
  // Member: acc_calibrate
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.acc_calibrate = tmp ? true : false;
  }

  // Member: mag_calibrate
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.mag_calibrate = tmp ? true : false;
  }

  // Member: gyro_calibrate
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.gyro_calibrate = tmp ? true : false;
  }

  return true;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
get_serialized_size(
  const hardware_msg::msg::ImuParameters & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: acc_calibrate
  {
    size_t item_size = sizeof(ros_message.acc_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: mag_calibrate
  {
    size_t item_size = sizeof(ros_message.mag_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: gyro_calibrate
  {
    size_t item_size = sizeof(ros_message.gyro_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
max_serialized_size_ImuParameters(
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

  // Member: acc_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // Member: mag_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // Member: gyro_calibrate
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
    using DataType = hardware_msg::msg::ImuParameters;
    is_plain =
      (
      offsetof(DataType, gyro_calibrate) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
cdr_serialize_key(
  const hardware_msg::msg::ImuParameters & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: acc_calibrate
  cdr << (ros_message.acc_calibrate ? true : false);

  // Member: mag_calibrate
  cdr << (ros_message.mag_calibrate ? true : false);

  // Member: gyro_calibrate
  cdr << (ros_message.gyro_calibrate ? true : false);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
get_serialized_size_key(
  const hardware_msg::msg::ImuParameters & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: acc_calibrate
  {
    size_t item_size = sizeof(ros_message.acc_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: mag_calibrate
  {
    size_t item_size = sizeof(ros_message.mag_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: gyro_calibrate
  {
    size_t item_size = sizeof(ros_message.gyro_calibrate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hardware_msg
max_serialized_size_key_ImuParameters(
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

  // Member: acc_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: mag_calibrate
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: gyro_calibrate
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
    using DataType = hardware_msg::msg::ImuParameters;
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
  auto typed_message =
    static_cast<const hardware_msg::msg::ImuParameters *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ImuParameters__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<hardware_msg::msg::ImuParameters *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ImuParameters__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const hardware_msg::msg::ImuParameters *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ImuParameters__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ImuParameters(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ImuParameters__callbacks = {
  "hardware_msg::msg",
  "ImuParameters",
  _ImuParameters__cdr_serialize,
  _ImuParameters__cdr_deserialize,
  _ImuParameters__get_serialized_size,
  _ImuParameters__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _ImuParameters__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ImuParameters__callbacks,
  get_message_typesupport_handle_function,
  &hardware_msg__msg__ImuParameters__get_type_hash,
  &hardware_msg__msg__ImuParameters__get_type_description,
  &hardware_msg__msg__ImuParameters__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace hardware_msg

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_hardware_msg
const rosidl_message_type_support_t *
get_message_type_support_handle<hardware_msg::msg::ImuParameters>()
{
  return &hardware_msg::msg::typesupport_fastrtps_cpp::_ImuParameters__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, hardware_msg, msg, ImuParameters)() {
  return &hardware_msg::msg::typesupport_fastrtps_cpp::_ImuParameters__handle;
}

#ifdef __cplusplus
}
#endif
