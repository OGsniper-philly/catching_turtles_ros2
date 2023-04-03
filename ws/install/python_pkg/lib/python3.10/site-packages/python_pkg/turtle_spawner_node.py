import rclpy
from random import uniform
from math import pi
from functools import partial
from rclpy.node import Node
from turtlesim.srv import Spawn
from interfaces.msg import Turtle, TurtleArray
from interfaces.srv import CatchTurtle
from turtlesim.srv import Kill

class TurtleSpawnerNode(Node):
    """Node to handle spawn and kill services of to-catch turtles in turtlesim window"""
    def __init__(self):
        super().__init__("turtle_spawner_node")
        self.get_logger().info("turtle_spawner_node started...")
        # Spawn timer to call turtlesim window spawn service
        self.spawn_timer = self.create_timer(1, self.spawn_timer_callback)
        # Publish alive turtles
        self.turtle_pub = self.create_publisher(TurtleArray, "/alive_turtles", 10)
        self.turtle_array = TurtleArray()

        # Catch turtle service
        self.catch_service = self.create_service(CatchTurtle, "/catch_turtle", self.catch_service_callback)

    def catch_service_callback(self, request, response):
        """Catch turtle with requested name by calling turtlesim window kill service"""
        kill_client = self.create_client(Kill, "/kill")
        while not kill_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /kill service...")
        kill_request = Kill.Request()
        kill_request.name = request.name
        future = kill_client.call_async(kill_request)
        future.add_done_callback(partial(self.kill_service_callback, name=request.name))
        return response

    def kill_service_callback(self, future, name):
        try:
            response = future.result()
            # Remove turtle from alive turtles list
            for turtle in self.turtle_array.alive_turtles:
                if turtle.name == name:
                    self.turtle_array.alive_turtles.remove(turtle)
            # No need to publish since turtle_control_node already removed caught turtle
            self.get_logger().info("Killed {}".format(name))
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

    def spawn_timer_callback(self):
        """Call turtlesim window spawn service"""
        spawn_client = self.create_client(Spawn, "/spawn")
        while not spawn_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /spawn service...")
        request = Spawn.Request()
        request.x = uniform(0, 11)
        request.y = uniform(0, 11)
        request.theta = uniform(0, 2*pi)
        future = spawn_client.call_async(request)
        future.add_done_callback(partial(self.spawn_service_callback, x=request.x, y=request.y, theta=request.theta))

    def spawn_service_callback(self, future, x, y, theta):
        """Handle turtlesim window spawn response"""
        try:
            response = future.result()
            self.get_logger().info("spawned {} at ({}, {})".format(response.name, x, y))
            # Add turtle in alive turtles
            new_turtle = Turtle()
            new_turtle.name = response.name
            new_turtle.pose[0] = x
            new_turtle.pose[1] = y
            new_turtle.pose[2] = theta
            self.turtle_array.alive_turtles.append(new_turtle)
            # Send updated array
            self.turtle_pub.publish(self.turtle_array)
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))


def main(args=None):
    rclpy.init(args=args)
    node = TurtleSpawnerNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()