from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import SetEnvironmentVariable, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    tinker_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('tinker'),
                'launch',
                'description.launch.py'
            )
        ])
    )

    return LaunchDescription(
        [
            # Запуск description
            tinker_launch,
            Node(
                package="tinker_gui",
                executable="gui_slider_node.py",
                name="gui_slider_node",
                output="screen",
            ),
            Node(
                package="tinker_gui",
                executable="states_to_joint_states.py",
                name="states_to_joint_states",
                output="screen",
            ),
            Node(
                package="tinker_gui",
                executable="commands_to_states_bridge.py",
                name="commands_to_states_bridge",
                output="screen",
            ),
        ]
    )
