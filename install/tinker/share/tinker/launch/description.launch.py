import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration, Command, FindExecutable
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch.conditions import UnlessCondition


def generate_launch_description():
    # Проверка использования времени симуляции
    use_sim_time = LaunchConfiguration("use_sim_time")

    # Пути к файлам
    pkg_path = os.path.join(get_package_share_directory("tinker"))
    xacro_file = os.path.join(pkg_path, "urdf", "tinker_1.urdf.xacro")
    # rviz_config_file = os.path.join(pkg_path, "rviz", "slam.rviz")

    # Описание робота
    robot_description = ParameterValue(
        Command([FindExecutable(name='xacro'), ' ', xacro_file]),
        value_type=str,
    )
    robot_description_param = {
        "robot_description": robot_description,
        "use_sim_time": use_sim_time,
        "ignore_timestamp": False,  # Критически важный параметр ?
    }

    # Узел robot_state_publisher
    node_robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[robot_description_param],
    )

    # (Опционально) узел joint_state_publisher_gui
    # Для дифф. робота обычно не нужен, но если хотите видеть слайдеры, оставьте
    joint_state_publisher_node = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
        name="joint_state_publisher_gui",
        output="screen",
    )

    # Узел RViz
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        # arguments=["-d", rviz_config_file],
        parameters=[{"use_sim_time": use_sim_time}],
        output="screen",
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "use_sim_time",
                default_value="false",
                description="Use sim time if true",
            ),
            node_robot_state_publisher,
            joint_state_publisher_node,
            rviz_node,
        ]
    )
