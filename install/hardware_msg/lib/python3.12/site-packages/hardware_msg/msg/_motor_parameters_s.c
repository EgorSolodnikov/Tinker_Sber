// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from hardware_msg:msg/MotorParameters.idl
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
#include "hardware_msg/msg/detail/motor_parameters__struct.h"
#include "hardware_msg/msg/detail/motor_parameters__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool hardware_msg__msg__motor_parameters__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[51];
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
    assert(strncmp("hardware_msg.msg._motor_parameters.MotorParameters", full_classname_dest, 50) == 0);
  }
  hardware_msg__msg__MotorParameters * ros_message = _ros_message;
  {  // enable
    PyObject * field = PyObject_GetAttrString(_pymsg, "enable");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->enable = (Py_True == field);
    Py_DECREF(field);
  }
  {  // reset_zero
    PyObject * field = PyObject_GetAttrString(_pymsg, "reset_zero");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->reset_zero = (Py_True == field);
    Py_DECREF(field);
  }
  {  // reset_error
    PyObject * field = PyObject_GetAttrString(_pymsg, "reset_error");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->reset_error = (Py_True == field);
    Py_DECREF(field);
  }
  {  // kp
    PyObject * field = PyObject_GetAttrString(_pymsg, "kp");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->kp = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // kd
    PyObject * field = PyObject_GetAttrString(_pymsg, "kd");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->kd = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * hardware_msg__msg__motor_parameters__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MotorParameters */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("hardware_msg.msg._motor_parameters");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MotorParameters");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  hardware_msg__msg__MotorParameters * ros_message = (hardware_msg__msg__MotorParameters *)raw_ros_message;
  {  // enable
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->enable ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "enable", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reset_zero
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->reset_zero ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reset_zero", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reset_error
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->reset_error ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reset_error", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // kp
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->kp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "kp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // kd
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->kd);
    {
      int rc = PyObject_SetAttrString(_pymessage, "kd", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
