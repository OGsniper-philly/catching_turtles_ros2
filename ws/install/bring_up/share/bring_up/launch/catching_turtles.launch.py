import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    config = os.path.join(
        get_package_share_directory("bring_up"),
        "config",
        "params.yaml"
    )

    return LaunchDescription([
        # Python nodes
        Node(
            package='turtlesim',
            namespace='sim1',            
            executable='turtlesim_node',
            name='turtlesim1',
        ),
        Node(
            package='python_pkg',
            executable='turtle_control_node',
            name="turtle_control_python",
            remappings=[
                ("/alive_turtles", "/sim1/alive_turtles"),
                ("/turtle1/pose", "/sim1/turtle1/pose"),
                ("/turtle1/cmd_vel", "/sim1/turtle1/cmd_vel"),
                ("/catch_turtle", "/sim1/catch_turtle"),
                ("/turtle1/set_pen", "/sim1/turtle1/set_pen")
            ],
            parameters=[config]
        ),
        Node(
            package='python_pkg',
            executable='turtle_spawner_node',
            name="turtle_spawner_python",
            remappings=[
                ("/spawn", "/sim1/spawn"),
                ("/kill", "/sim1/kill"),
                ("/catch_turtle", "/sim1/catch_turtle"),
                ("/alive_turtles", "/sim1/alive_turtles")
            ],
            parameters=[config]
        ),
        # C++ nodes
        Node(
            package='turtlesim',
            namespace='sim2',
            executable='turtlesim_node',
            name='turtlesim2',
        ),
        Node(
            package='cpp_pkg',
            executable='turtle_control_node',
            name="turtle_control_cpp",
            remappings=[
                ("/alive_turtles", "/sim2/alive_turtles"),
                ("/turtle1/pose", "/sim2/turtle1/pose"),
                ("/turtle1/cmd_vel", "/sim2/turtle1/cmd_vel"),
                ("/catch_turtle", "/sim2/catch_turtle"),
                ("/turtle1/set_pen", "/sim2/turtle1/set_pen")
            ],
            parameters=[config]
        ),
        Node(
            package='cpp_pkg',
            executable='turtle_spawner_node',
            name="turtle_spawner_cpp",
            remappings=[
                ("/spawn", "/sim2/spawn"),
                ("/kill", "/sim2/kill"),
                ("/catch_turtle", "/sim2/catch_turtle"),
                ("/alive_turtles", "/sim2/alive_turtles")
            ],
            parameters=[config]
        )
    ])