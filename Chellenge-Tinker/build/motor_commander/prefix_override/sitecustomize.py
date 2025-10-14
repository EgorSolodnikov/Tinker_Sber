import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/mnt/c/tinker/Tinker_Sber/Chellenge-Tinker/install/motor_commander'
