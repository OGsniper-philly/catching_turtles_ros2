from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Python nodes
        Node(
            package='turtlesim',
            namespace='sim1',            
            executable='turtlesim_node',
        ),
        Node(
            package='python_pkg',
            # namespace='sim1',
            executable='turtle_control_node',
            remappings=[
                ("/alive_turtles", "/sim1/alive_turtles"),
                ("/turtle1/pose", "/sim1/turtle1/pose"),
                ("/turtle1/cmd_vel", "/sim1/turtle1/cmd_vel"),
                ("/catch_turtle", "/sim1/catch_turtle"),
                ("/turtle1/set_pen", "/sim1/turtle1/set_pen")
            ]
        ),
        Node(
            package='python_pkg',
            # namespace='sim1',
            executable='turtle_spawner_node',
            remappings=[
                ("/spawn", "/sim1/spawn"),
                ("/kill", "/sim1/kill"),
                ("/catch_turtle", "/sim1/catch_turtle"),
                ("/alive_turtles", "/sim1/alive_turtles")
            ]
        ),
        # C++ nodes
        Node(
            package='turtlesim',
            namespace='sim2',
            executable='turtlesim_node',
        ),
        Node(
            package='cpp_pkg',
            # namespace='sim2',
            executable='turtle_control_node',
            remappings=[
                ("/alive_turtles", "/sim2/alive_turtles"),
                ("/turtle1/pose", "/sim2/turtle1/pose"),
                ("/turtle1/cmd_vel", "/sim2/turtle1/cmd_vel"),
                ("/catch_turtle", "/sim2/catch_turtle")
            ]
        ),
        Node(
            package='cpp_pkg',
            # namespace='sim2',
            executable='turtle_spawner_node',
            remappings=[
                ("/spawn", "/sim2/spawn"),
                ("/kill", "/sim2/kill"),
                ("/catch_turtle", "/sim2/catch_turtle"),
                ("/alive_turtles", "/sim2/alive_turtles")
            ]
        )
        ])