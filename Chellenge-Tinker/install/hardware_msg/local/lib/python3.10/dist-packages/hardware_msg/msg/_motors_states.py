# generated from rosidl_generator_py/resource/_idl.py.em
# with input from hardware_msg:msg/MotorsStates.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

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
    ]

    _fields_and_field_types = {
        'current_pos': 'float',
        'current_vel': 'float',
        'current_trq': 'float',
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
        self.current_pos = kwargs.get('current_pos', float())
        self.current_vel = kwargs.get('current_vel', float())
        self.current_trq = kwargs.get('current_trq', float())

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
        if self.current_pos != other.current_pos:
            return False
        if self.current_vel != other.current_vel:
            return False
        if self.current_trq != other.current_trq:
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
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current_pos' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current_pos' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current_pos = value

    @builtins.property
    def current_vel(self):
        """Message field 'current_vel'."""
        return self._current_vel

    @current_vel.setter
    def current_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current_vel = value

    @builtins.property
    def current_trq(self):
        """Message field 'current_trq'."""
        return self._current_trq

    @current_trq.setter
    def current_trq(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'current_trq' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'current_trq' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._current_trq = value
