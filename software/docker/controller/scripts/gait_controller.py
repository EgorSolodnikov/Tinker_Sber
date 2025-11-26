import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, TargetCommand, ControlCommand
from .adapter_factory import AdapterFactory
from .inference_model import InferenceModel

class GaitController(Node):
    def __init__(self, adapter_type: str, input_device: str = 'keyboard'):
        super().__init__('gait_controller')

        self.adapter_type = adapter_type
        self.input_device = input_device

        self.adapter = AdapterFactory.get(adapter_type, node=self)
        self.adapter.initialize()

        self.inference_model = InferenceModel('path/to/model.onnx') # concept of interaction with model

        self.target_subscription = self.create_subscription(
            TargetCommand,
            '/control/target',
            10
        )

