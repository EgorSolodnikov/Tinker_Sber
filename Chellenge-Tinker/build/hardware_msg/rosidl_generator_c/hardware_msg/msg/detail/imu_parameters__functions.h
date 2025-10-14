// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "hardware_msg/msg/imu_parameters.h"


#ifndef HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__FUNCTIONS_H_
#define HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "hardware_msg/msg/rosidl_generator_c__visibility_control.h"

#include "hardware_msg/msg/detail/imu_parameters__struct.h"

/// Initialize msg/ImuParameters message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hardware_msg__msg__ImuParameters
 * )) before or use
 * hardware_msg__msg__ImuParameters__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__ImuParameters__init(hardware_msg__msg__ImuParameters * msg);

/// Finalize msg/ImuParameters message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__ImuParameters__fini(hardware_msg__msg__ImuParameters * msg);

/// Create msg/ImuParameters message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hardware_msg__msg__ImuParameters__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
hardware_msg__msg__ImuParameters *
hardware_msg__msg__ImuParameters__create(void);

/// Destroy msg/ImuParameters message.
/**
 * It calls
 * hardware_msg__msg__ImuParameters__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__ImuParameters__destroy(hardware_msg__msg__ImuParameters * msg);

/// Check for msg/ImuParameters message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__ImuParameters__are_equal(const hardware_msg__msg__ImuParameters * lhs, const hardware_msg__msg__ImuParameters * rhs);

/// Copy a msg/ImuParameters message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__ImuParameters__copy(
  const hardware_msg__msg__ImuParameters * input,
  hardware_msg__msg__ImuParameters * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_type_hash_t *
hardware_msg__msg__ImuParameters__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_runtime_c__type_description__TypeDescription *
hardware_msg__msg__ImuParameters__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_runtime_c__type_description__TypeSource *
hardware_msg__msg__ImuParameters__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
const rosidl_runtime_c__type_description__TypeSource__Sequence *
hardware_msg__msg__ImuParameters__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/ImuParameters messages.
/**
 * It allocates the memory for the number of elements and calls
 * hardware_msg__msg__ImuParameters__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__ImuParameters__Sequence__init(hardware_msg__msg__ImuParameters__Sequence * array, size_t size);

/// Finalize array of msg/ImuParameters messages.
/**
 * It calls
 * hardware_msg__msg__ImuParameters__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__ImuParameters__Sequence__fini(hardware_msg__msg__ImuParameters__Sequence * array);

/// Create array of msg/ImuParameters messages.
/**
 * It allocates the memory for the array and calls
 * hardware_msg__msg__ImuParameters__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
hardware_msg__msg__ImuParameters__Sequence *
hardware_msg__msg__ImuParameters__Sequence__create(size_t size);

/// Destroy array of msg/ImuParameters messages.
/**
 * It calls
 * hardware_msg__msg__ImuParameters__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__ImuParameters__Sequence__destroy(hardware_msg__msg__ImuParameters__Sequence * array);

/// Check for msg/ImuParameters message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__ImuParameters__Sequence__are_equal(const hardware_msg__msg__ImuParameters__Sequence * lhs, const hardware_msg__msg__ImuParameters__Sequence * rhs);

/// Copy an array of msg/ImuParameters messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__ImuParameters__Sequence__copy(
  const hardware_msg__msg__ImuParameters__Sequence * input,
  hardware_msg__msg__ImuParameters__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__IMU_PARAMETERS__FUNCTIONS_H_
