import rclpy
from rclpy.node import Node
from controller_msg.msg import RobotState, TargetCommand, ControlCommand
from .factories import AdapterFactory, InputDeviceFactory
from .inference_model import InferenceModel

class GaitController(Node):
    def __init__(self, adapter_type: str,
                 device_type: str = 'keyboard',
                 model_path: str = './models/model_30000.pt'):
        super().__init__('gait_controller')

        self.adapter_type = adapter_type
        self.device_type = device_type

        self.adapter = AdapterFactory.get_adapter(adapter_type, node=self)
        self.adapter.initialize()

        self.device = InputDeviceFactory.get_device(device_type, node=self)
        self.device.initialize()

        self.inference_model = InferenceModel(model_path)

        self.current_command = None
        self.current_state = None
        
        self.control_command = None

        self.control_timer = self.create_timer(0.01, self.control_loop)
        
        self.get_logger().info(
            f"Gait controller initialized with {adapter_type} adapter and {device_type} input"
        )

    def control_loop(self):
        try:
            action = self.inference_model.run(self.control_command)
            self.adapter.publish_control(action)
        except Exception as e:
            self.get_logger().error(f"Control loop error: {e}")

    def shutdown(self):
        self.adapter.shutdown()
        self.destroy_node()

