# generated from rosidl_generator_py/resource/_idl.py.em
# with input from hardware_msg:msg/MotorsCommands.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

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
    ]

    _fields_and_field_types = {
        'target_pos': 'float',
        'target_vel': 'float',
        'target_trq': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.target_pos = kwargs.get('target_pos', float())
        self.target_vel = kwargs.get('target_vel', float())
        self.target_trq = kwargs.get('target_trq', float())

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
        if self.target_pos != other.target_pos:
            return False
        if self.target_vel != other.target_vel:
            return False
        if self.target_trq != other.target_trq:
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
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'target_pos' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_pos' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_pos = value

    @builtins.property
    def target_vel(self):
        """Message field 'target_vel'."""
        return self._target_vel

    @target_vel.setter
    def target_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'target_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_vel = value

    @builtins.property
    def target_trq(self):
        """Message field 'target_trq'."""
        return self._target_trq

    @target_trq.setter
    def target_trq(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'target_trq' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_trq' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_trq = value
