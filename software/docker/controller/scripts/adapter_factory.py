from rclpy.node import Node
from .adapters import BaseAdapter, IsaacAdapter, MujocoAdapter, RobotAdapter

class AdapterFactory:
    
    _ADAPTER_MAP = {
        'isaac': IsaacAdapter,
        'mujoco': MujocoAdapter,
        'robot': RobotAdapter
    }

    @staticmethod
    def get(adapter_type: str, node: Node) -> BaseAdapter:
        adater_class = AdapterFactory._ADAPTER_MAP.get(adapter_type.lower())

        if adater_class is None:
            raise ValueError(f'Unknown adapter (control object) type: {adapter_type}')
        
        return adater_class(node)