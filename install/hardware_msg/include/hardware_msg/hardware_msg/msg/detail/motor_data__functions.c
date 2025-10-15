// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hardware_msg:msg/MotorData.idl
// generated code does not contain a copyright notice
#include "hardware_msg/msg/detail/motor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
hardware_msg__msg__MotorData__init(hardware_msg__msg__MotorData * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // connect
  // motor_connected
  // ready
  return true;
}

void
hardware_msg__msg__MotorData__fini(hardware_msg__msg__MotorData * msg)
{
  if (!msg) {
    return;
  }
  // id
  // connect
  // motor_connected
  // ready
}

bool
hardware_msg__msg__MotorData__are_equal(const hardware_msg__msg__MotorData * lhs, const hardware_msg__msg__MotorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // connect
  if (lhs->connect != rhs->connect) {
    return false;
  }
  // motor_connected
  if (lhs->motor_connected != rhs->motor_connected) {
    return false;
  }
  // ready
  if (lhs->ready != rhs->ready) {
    return false;
  }
  return true;
}

bool
hardware_msg__msg__MotorData__copy(
  const hardware_msg__msg__MotorData * input,
  hardware_msg__msg__MotorData * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // connect
  output->connect = input->connect;
  // motor_connected
  output->motor_connected = input->motor_connected;
  // ready
  output->ready = input->ready;
  return true;
}

hardware_msg__msg__MotorData *
hardware_msg__msg__MotorData__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hardware_msg__msg__MotorData * msg = (hardware_msg__msg__MotorData *)allocator.allocate(sizeof(hardware_msg__msg__MotorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hardware_msg__msg__MotorData));
  bool success = hardware_msg__msg__MotorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
hardware_msg__msg__MotorData__destroy(hardware_msg__msg__MotorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    hardware_msg__msg__MotorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
hardware_msg__msg__MotorData__Sequence__init(hardware_msg__msg__MotorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hardware_msg__msg__MotorData * data = NULL;

  if (size) {
    data = (hardware_msg__msg__MotorData *)allocator.zero_allocate(size, sizeof(hardware_msg__msg__MotorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hardware_msg__msg__MotorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hardware_msg__msg__MotorData__fini(&data[i - 1]);
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
hardware_msg__msg__MotorData__Sequence__fini(hardware_msg__msg__MotorData__Sequence * array)
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
      hardware_msg__msg__MotorData__fini(&array->data[i]);
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

hardware_msg__msg__MotorData__Sequence *
hardware_msg__msg__MotorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  hardware_msg__msg__MotorData__Sequence * array = (hardware_msg__msg__MotorData__Sequence *)allocator.allocate(sizeof(hardware_msg__msg__MotorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = hardware_msg__msg__MotorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
hardware_msg__msg__MotorData__Sequence__destroy(hardware_msg__msg__MotorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    hardware_msg__msg__MotorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
hardware_msg__msg__MotorData__Sequence__are_equal(const hardware_msg__msg__MotorData__Sequence * lhs, const hardware_msg__msg__MotorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!hardware_msg__msg__MotorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
hardware_msg__msg__MotorData__Sequence__copy(
  const hardware_msg__msg__MotorData__Sequence * input,
  hardware_msg__msg__MotorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(hardware_msg__msg__MotorData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    hardware_msg__msg__MotorData * data =
      (hardware_msg__msg__MotorData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!hardware_msg__msg__MotorData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          hardware_msg__msg__MotorData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!hardware_msg__msg__MotorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
