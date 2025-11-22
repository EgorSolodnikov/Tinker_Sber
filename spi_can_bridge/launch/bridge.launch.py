from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='spi_can_bridge',
            executable='spi_can_bridge',
            name='spi_can_bridge',
            output='screen'
        ),
    ])
