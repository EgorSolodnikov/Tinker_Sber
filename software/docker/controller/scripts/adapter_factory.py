from .isaac_adapter import IsaacAdapter
from .mujoco_adapter import MujocoAdapter
from .robot_adapter import RobotAdapter
from .base_adapter import BaseRobotAdapter
from rclpy.node import Node

class AdapterFactory:
    @staticmethod
    def create_adapter(adapter_type: str, node: Node) -> BaseRobotAdapter:
        adapter_type = adapter_type.lower()
        
        if adapter_type == 'isaac':
            return IsaacAdapter(node)
        elif adapter_type == 'mujoco':
            return MujocoAdapter(node)
        elif adapter_type == 'robot':
            return RobotAdapter(node)
        else:
            raise ValueError(f"Unknown adapter type: {adapter_type}")