// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from hardware_msg:msg/MotorParameters.idl
// generated code does not contain a copyright notice

#ifndef HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__FUNCTIONS_H_
#define HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "hardware_msg/msg/rosidl_generator_c__visibility_control.h"

#include "hardware_msg/msg/detail/motor_parameters__struct.h"

/// Initialize msg/MotorParameters message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * hardware_msg__msg__MotorParameters
 * )) before or use
 * hardware_msg__msg__MotorParameters__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__MotorParameters__init(hardware_msg__msg__MotorParameters * msg);

/// Finalize msg/MotorParameters message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__MotorParameters__fini(hardware_msg__msg__MotorParameters * msg);

/// Create msg/MotorParameters message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * hardware_msg__msg__MotorParameters__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
hardware_msg__msg__MotorParameters *
hardware_msg__msg__MotorParameters__create();

/// Destroy msg/MotorParameters message.
/**
 * It calls
 * hardware_msg__msg__MotorParameters__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__MotorParameters__destroy(hardware_msg__msg__MotorParameters * msg);

/// Check for msg/MotorParameters message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__MotorParameters__are_equal(const hardware_msg__msg__MotorParameters * lhs, const hardware_msg__msg__MotorParameters * rhs);

/// Copy a msg/MotorParameters message.
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
hardware_msg__msg__MotorParameters__copy(
  const hardware_msg__msg__MotorParameters * input,
  hardware_msg__msg__MotorParameters * output);

/// Initialize array of msg/MotorParameters messages.
/**
 * It allocates the memory for the number of elements and calls
 * hardware_msg__msg__MotorParameters__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__MotorParameters__Sequence__init(hardware_msg__msg__MotorParameters__Sequence * array, size_t size);

/// Finalize array of msg/MotorParameters messages.
/**
 * It calls
 * hardware_msg__msg__MotorParameters__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__MotorParameters__Sequence__fini(hardware_msg__msg__MotorParameters__Sequence * array);

/// Create array of msg/MotorParameters messages.
/**
 * It allocates the memory for the array and calls
 * hardware_msg__msg__MotorParameters__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
hardware_msg__msg__MotorParameters__Sequence *
hardware_msg__msg__MotorParameters__Sequence__create(size_t size);

/// Destroy array of msg/MotorParameters messages.
/**
 * It calls
 * hardware_msg__msg__MotorParameters__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
void
hardware_msg__msg__MotorParameters__Sequence__destroy(hardware_msg__msg__MotorParameters__Sequence * array);

/// Check for msg/MotorParameters message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_hardware_msg
bool
hardware_msg__msg__MotorParameters__Sequence__are_equal(const hardware_msg__msg__MotorParameters__Sequence * lhs, const hardware_msg__msg__MotorParameters__Sequence * rhs);

/// Copy an array of msg/MotorParameters messages.
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
hardware_msg__msg__MotorParameters__Sequence__copy(
  const hardware_msg__msg__MotorParameters__Sequence * input,
  hardware_msg__msg__MotorParameters__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // HARDWARE_MSG__MSG__DETAIL__MOTOR_PARAMETERS__FUNCTIONS_H_
