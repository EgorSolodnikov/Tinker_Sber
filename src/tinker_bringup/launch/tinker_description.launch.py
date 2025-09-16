from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    urdf_path = os.path.join(
        get_package_share_directory('tinker_bringup'),
        'urdf',
        'tinker_urdf.urdf'
    )
    
    with open(urdf_path, 'r') as infp:
        robot_desc = infp.read()

    return LaunchDescription([
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'robot_description': robot_desc}]
        ),
        Node(
            package='tinker_bringup',
            executable='tinker_bringup',
            name='tinker_bringup',
            output='screen',
            parameters=[{'joint_names': ['joint_l_yaw', 'joint_l_roll', 'joint_l_pitch', 'joint_l_knee', 'joint_l_ankle', 'joint_r_yaw', 'joint_r_roll', 'joint_r_pitch', 'joint_r_knee', 'joint_r_ankle', ]}]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'world', 'base_link']
        )
    ])