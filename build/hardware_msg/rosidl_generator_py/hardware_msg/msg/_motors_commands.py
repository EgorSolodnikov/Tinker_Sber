# generated from rosidl_generator_py/resource/_idl.py.em
# with input from hardware_msg:msg/MotorsCommands.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'target_pos'
# Member 'target_vel'
# Member 'target_trq'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MotorsCommands(type):
    """Metaclass of message 'MotorsCommands'."""

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
                'hardware_msg.msg.MotorsCommands')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motors_commands
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motors_commands
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motors_commands
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motors_commands
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motors_commands

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MotorsCommands(metaclass=Metaclass_MotorsCommands):
    """Message class 'MotorsCommands'."""

    __slots__ = [
        '_target_pos',
        '_target_vel',
        '_target_trq',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'target_pos': 'float[10]',
        'target_vel': 'float[10]',
        'target_trq': 'float[10]',
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
        if 'target_pos' not in kwargs:
            self.target_pos = numpy.zeros(10, dtype=numpy.float32)
        else:
            self.target_pos = numpy.array(kwargs.get('target_pos'), dtype=numpy.float32)
            assert self.target_pos.shape == (10, )
        if 'target_vel' not in kwargs:
            self.target_vel = numpy.zeros(10, dtype=numpy.float32)
        else:
            self.target_vel = numpy.array(kwargs.get('target_vel'), dtype=numpy.float32)
            assert self.target_vel.shape == (10, )
        if 'target_trq' not in kwargs:
            self.target_trq = numpy.zeros(10, dtype=numpy.float32)
        else:
            self.target_trq = numpy.array(kwargs.get('target_trq'), dtype=numpy.float32)
            assert self.target_trq.shape == (10, )

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
        if all(self.target_pos != other.target_pos):
            return False
        if all(self.target_vel != other.target_vel):
            return False
        if all(self.target_trq != other.target_trq):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def target_pos(self):
        """Message field 'target_pos'."""
        return self._target_pos

    @target_pos.setter
    def target_pos(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'target_pos' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 10, \
                    "The 'target_pos' numpy.ndarray() must have a size of 10"
                self._target_pos = value
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
                "The 'target_pos' field must be a set or sequence with length 10 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._target_pos = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def target_vel(self):
        """Message field 'target_vel'."""
        return self._target_vel

    @target_vel.setter
    def target_vel(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'target_vel' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 10, \
                    "The 'target_vel' numpy.ndarray() must have a size of 10"
                self._target_vel = value
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
                "The 'target_vel' field must be a set or sequence with length 10 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._target_vel = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def target_trq(self):
        """Message field 'target_trq'."""
        return self._target_trq

    @target_trq.setter
    def target_trq(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float32, \
                    "The 'target_trq' numpy.ndarray() must have the dtype of 'numpy.float32'"
                assert value.size == 10, \
                    "The 'target_trq' numpy.ndarray() must have a size of 10"
                self._target_trq = value
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
                "The 'target_trq' field must be a set or sequence with length 10 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._target_trq = numpy.array(value, dtype=numpy.float32)
