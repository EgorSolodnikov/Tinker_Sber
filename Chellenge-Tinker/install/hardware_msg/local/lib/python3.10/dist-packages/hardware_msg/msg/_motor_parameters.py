# generated from rosidl_generator_py/resource/_idl.py.em
# with input from hardware_msg:msg/MotorParameters.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MotorParameters(type):
    """Metaclass of message 'MotorParameters'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('hardware_msg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'hardware_msg.msg.MotorParameters')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motor_parameters
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motor_parameters
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motor_parameters
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motor_parameters
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motor_parameters

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MotorParameters(metaclass=Metaclass_MotorParameters):
    """Message class 'MotorParameters'."""

    __slots__ = [
        '_enable',
        '_reset_zero',
        '_reset_error',
        '_kp',
        '_kd',
    ]

    _fields_and_field_types = {
        'enable': 'boolean',
        'reset_zero': 'boolean',
        'reset_error': 'boolean',
        'kp': 'float',
        'kd': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.enable = kwargs.get('enable', bool())
        self.reset_zero = kwargs.get('reset_zero', bool())
        self.reset_error = kwargs.get('reset_error', bool())
        self.kp = kwargs.get('kp', float())
        self.kd = kwargs.get('kd', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.enable != other.enable:
            return False
        if self.reset_zero != other.reset_zero:
            return False
        if self.reset_error != other.reset_error:
            return False
        if self.kp != other.kp:
            return False
        if self.kd != other.kd:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def enable(self):
        """Message field 'enable'."""
        return self._enable

    @enable.setter
    def enable(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'enable' field must be of type 'bool'"
        self._enable = value

    @builtins.property
    def reset_zero(self):
        """Message field 'reset_zero'."""
        return self._reset_zero

    @reset_zero.setter
    def reset_zero(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'reset_zero' field must be of type 'bool'"
        self._reset_zero = value

    @builtins.property
    def reset_error(self):
        """Message field 'reset_error'."""
        return self._reset_error

    @reset_error.setter
    def reset_error(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'reset_error' field must be of type 'bool'"
        self._reset_error = value

    @builtins.property
    def kp(self):
        """Message field 'kp'."""
        return self._kp

    @kp.setter
    def kp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'kp' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'kp' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._kp = value

    @builtins.property
    def kd(self):
        """Message field 'kd'."""
        return self._kd

    @kd.setter
    def kd(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'kd' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'kd' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._kd = value
