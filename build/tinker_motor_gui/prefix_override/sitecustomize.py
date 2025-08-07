import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/dmitrytorov/tinker_ros2/install/tinker_motor_gui'
