# generated from rosidl_generator_py/resource/_idl.py.em
# with input from hardware_msg:msg/MotorsStates.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'current_pos'
# Member 'current_vel'
# Member 'current_trq'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MotorsStates(type):
    """Metaclass of message 'MotorsStates'."""

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
                'hardware_msg.msg.MotorsStates')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motors_states
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motors_states
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motors_states
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motors_states
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motors_states

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MotorsStates(metaclass=Metaclass_MotorsStates):
    """Message class 'MotorsStates'."""

    __slots__ = [
        '_current_pos',
        '_current_vel',
        '_current_trq',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'current_pos': 'float[10]',
        'current_vel': 'float[10]',
        'current_trq': 'float[10]',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 10),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 10),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 10),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        if 'current_pos' not in kwargs:
            self.current_pos = numpy.zeros(10, dtype=numpy.float32)
        else:
            self.current_pos = numpy.array(kwargs.get('current_pos'), dtype=numpy.float32)
            assert self.current_pos.shape == (10, )
        if 'current_vel' not in kwargs:
            self.current_vel = numpy.zeros(10, dtype=numpy.float32)
        else:
            self.current_vel = numpy.array(kwargs.get('current_vel'), dtype=numpy.float32)
            assert self.current_vel.shape == (10, )
        if 'current_trq' not in kwargs:
            self.current_trq = numpy.zeros(10, dtype=numpy.float32)
        else:
            self.current_trq = numpy.array(kwargs.get('current_trq'), dtype=numpy.float32)
            assert self.current_trq.shape == (10, )

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
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
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if all(self.current_pos != other.current_pos):
            return False
        if all(self.current_vel != other.current_vel):
            return False
        if all(self.current_trq != other.current_trq):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def current_pos(self):
        """Message field 'current_pos'."""
        return self._current_pos

    @current_pos.setter
    def current_pos(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'current_pos' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 10, \
                    "The 'current_pos' numpy.ndarray() must have a size of 10"
                self._current_pos = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 10 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'current_pos' field must be a set or sequence with length 10 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._current_pos = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def current_vel(self):
        """Message field 'current_vel'."""
        return self._current_vel

    @current_vel.setter
    def current_vel(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'current_vel' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 10, \
                    "The 'current_vel' numpy.ndarray() must have a size of 10"
                self._current_vel = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 10 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'current_vel' field must be a set or sequence with length 10 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._current_vel = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def current_trq(self):
        """Message field 'current_trq'."""
        return self._current_trq

    @current_trq.setter
    def current_trq(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'current_trq' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 10, \
                    "The 'current_trq' numpy.ndarray() must have a size of 10"
                self._current_trq = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 10 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'current_trq' field must be a set or sequence with length 10 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._current_trq = numpy.array(value, dtype=numpy.float32)
