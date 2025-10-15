// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hardware_msg:msg/ImuParameters.idl
// generated code does not contain a copyright notice
#include "hardware_msg/msg/detail/imu_parameters__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hardware_msg__msg__ImuParameters__init(hardware_msg__msg__ImuParameters * msg)
{
  if (!msg) {
    return false;
  }
  // acc_calibrate
  // msg_calibrate
  // gyro_calibrate
  return true;
}

void
hardware_msg__msg__ImuParameters__fini(hardware_msg__msg__ImuParameters * msg)
{
  if (!msg) {
    return;
  }
  // acc_calibrate
  // msg_calibrate
  // gyro_calibrate
}

bool
hardware_msg__msg__ImuParameters__are_equal(const hardware_msg__msg__ImuParameters * lhs, const hardware_msg__msg__ImuParameters * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // acc_calibrate
  if (lhs->acc_calibrate != rhs->acc_calibrate) {
    return false;
  }
  // msg_calibrate
  if (lhs->msg_calibrate != rhs->msg_calibrate) {
    return false;
  }
  // gyro_calibrate
  if (lhs->gyro_calibrate != rhs->gyro_calibrate) {
    return false;
  }
  return true;
}

bool
hardware_msg__msg__ImuParameters__copy(
  const hardware_msg__msg__ImuParameters * input,
  hardware_msg__msg__ImuParameters * output)
{
  if (!input || !output) {
    return false;
  }
  // acc_calibrate
  output->acc_calibrate = input->acc_calibrate;
  // msg_calibrate
  output->msg_calibrate = input->msg_calibrate;
  // gyro_calibrate
  output->gyro_calibrate = input->gyro_calibrate;
  return true;
}

hardware_msg__msg__ImuParameters *
hardware_msg__msg__ImuParameters__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hardware_msg__msg__ImuParameters * msg = (hardware_msg__msg__ImuParameters *)allocator.allocate(sizeof(hardware_msg__msg__ImuParameters), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hardware_msg__msg__ImuParameters));
  bool success = hardware_msg__msg__ImuParameters__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hardware_msg__msg__ImuParameters__destroy(hardware_msg__msg__ImuParameters * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hardware_msg__msg__ImuParameters__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hardware_msg__msg__ImuParameters__Sequence__init(hardware_msg__msg__ImuParameters__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hardware_msg__msg__ImuParameters * data = NULL;

  if (size) {
    data = (hardware_msg__msg__ImuParameters *)allocator.zero_allocate(size, sizeof(hardware_msg__msg__ImuParameters), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hardware_msg__msg__ImuParameters__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hardware_msg__msg__ImuParameters__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hardware_msg__msg__ImuParameters__Sequence__fini(hardware_msg__msg__ImuParameters__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hardware_msg__msg__ImuParameters__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hardware_msg__msg__ImuParameters__Sequence *
hardware_msg__msg__ImuParameters__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hardware_msg__msg__ImuParameters__Sequence * array = (hardware_msg__msg__ImuParameters__Sequence *)allocator.allocate(sizeof(hardware_msg__msg__ImuParameters__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hardware_msg__msg__ImuParameters__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hardware_msg__msg__ImuParameters__Sequence__destroy(hardware_msg__msg__ImuParameters__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hardware_msg__msg__ImuParameters__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hardware_msg__msg__ImuParameters__Sequence__are_equal(const hardware_msg__msg__ImuParameters__Sequence * lhs, const hardware_msg__msg__ImuParameters__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hardware_msg__msg__ImuParameters__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hardware_msg__msg__ImuParameters__Sequence__copy(
  const hardware_msg__msg__ImuParameters__Sequence * input,
  hardware_msg__msg__ImuParameters__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hardware_msg__msg__ImuParameters);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hardware_msg__msg__ImuParameters * data =
      (hardware_msg__msg__ImuParameters *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hardware_msg__msg__ImuParameters__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hardware_msg__msg__ImuParameters__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hardware_msg__msg__ImuParameters__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
