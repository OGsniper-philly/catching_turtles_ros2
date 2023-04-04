from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            executable='turtlesim_node',
        ),
        Node(
            package='python_pkg',
            executable='turtle_control_node',
        ),
        Node(
            package='python_pkg',
            executable='turtle_spawner_node',
        )
    ])