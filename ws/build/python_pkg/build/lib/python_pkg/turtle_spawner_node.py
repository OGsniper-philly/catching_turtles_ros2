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
    """Node to handle spawn and catch services of turtles in turtlesim window"""
    def __init__(self):
        super().__init__("turtle_spawner_node")
        self.get_logger().info("turtle_spawner_node started...")
        # Spawn timer 
        self.spawn_timer = self.create_timer(1, self.call_spawn_service)

        # Alive turtles publisher; publishes array when change occurs
        self.turtle_pub = self.create_publisher(TurtleArray, "/alive_turtles", 10)
        self.alive_turtles = []

        # Catch turtle service; simply calls the turtlesim window kill service
        self.catch_service = self.create_service(CatchTurtle, "/catch_turtle", self.call_kill_service)

    def call_kill_service(self, request, response):
        """Catch turtle with requested name by calling turtlesim window kill service"""
        kill_client = self.create_client(Kill, "/kill")
        while not kill_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /kill service...")
        kill_request = Kill.Request()
        kill_request.name = request.name
        future = kill_client.call_async(kill_request)
        future.add_done_callback(partial(self.kill_service_callback, name=request.name))
        # Must return response since still a service
        return response

    def kill_service_callback(self, future, name):
        """Turtlesim kill service callback"""
        try:
            response = future.result()
            # Remove turtle from alive turtles list
            for turtle in self.alive_turtles:
                if turtle.name == name:
                    self.alive_turtles.remove(turtle)
            # No need to publish since turtle_control_node already removed caught turtle
            self.get_logger().info("Killed {}".format(name))
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

    def call_spawn_service(self):
        """Call turtlesim window spawn service"""
        spawn_client = self.create_client(Spawn, "/spawn")
        while not spawn_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /spawn service...")
        request = Spawn.Request()
        request.x = uniform(0.5, 10.5)
        request.y = uniform(0.5, 10.5)
        request.theta = uniform(0, 2*pi)
        future = spawn_client.call_async(request)
        future.add_done_callback(partial(self.spawn_service_callback, x=request.x, y=request.y, theta=request.theta))

    def spawn_service_callback(self, future, x, y, theta):
        """Turtlesim spawn service callback"""
        try:
            response = future.result()
            self.get_logger().info("spawned {} at ({}, {}, theta: {})".format(response.name, x, y, theta))
            # Add turtle to alive turtles list
            new_turtle = Turtle()
            new_turtle.name = response.name
            new_turtle.pose[0] = x
            new_turtle.pose[1] = y
            new_turtle.pose[2] = theta
            self.alive_turtles.append(new_turtle)
            # Send updated array
            turtle_array = TurtleArray()
            turtle_array.alive_turtles = self.alive_turtles
            self.turtle_pub.publish(turtle_array)
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))


def main(args=None):
    rclpy.init(args=args)
    node = TurtleSpawnerNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()