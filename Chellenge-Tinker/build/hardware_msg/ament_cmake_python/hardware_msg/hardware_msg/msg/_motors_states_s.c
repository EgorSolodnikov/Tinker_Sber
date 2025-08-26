// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from hardware_msg:msg/MotorsStates.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "hardware_msg/msg/detail/motors_states__struct.h"
#include "hardware_msg/msg/detail/motors_states__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool hardware_msg__msg__motors_states__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[45];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("hardware_msg.msg._motors_states.MotorsStates", full_classname_dest, 44) == 0);
  }
  hardware_msg__msg__MotorsStates * ros_message = _ros_message;
  {  // current_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_pos");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current_pos = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // current_vel
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_vel");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current_vel = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // current_trq
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_trq");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->current_trq = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * hardware_msg__msg__motors_states__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MotorsStates */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("hardware_msg.msg._motors_states");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MotorsStates");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  hardware_msg__msg__MotorsStates * ros_message = (hardware_msg__msg__MotorsStates *)raw_ros_message;
  {  // current_pos
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current_vel
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current_vel);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_vel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // current_trq
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->current_trq);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_trq", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
