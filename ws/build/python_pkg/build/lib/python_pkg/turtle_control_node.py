import rclpy
from math import atan2, sqrt, pi
from random import randint
from rclpy.node import Node
from turtlesim.msg import Pose
from turtlesim.srv import SetPen
from geometry_msgs.msg import Twist
from interfaces.msg import TurtleArray
from interfaces.srv import CatchTurtle
from functools import partial

class TurtleControlNode(Node):
    """Node to control turtle1 and catch closest turtle available. Utilizes a P controller to output velocity targets"""
    def __init__(self):
        super().__init__("turtle_control_node")
        self.get_logger().info("turtle_control_node started...")
        # Turtle state subscriber
        self.state_sub = self.create_subscription(Pose, "/turtle1/pose", self.state_callback, 10)
        self.state = None

        # P controller loop at 100Hz
        self.control_timer = self.create_timer(0.01, self.p_control_loop)
        # Proportional gains; ratio found via testing
        self.k_pos = 3
        self.k_theta = 9

        # Velocity publisher
        self.vel_pub = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)

        # Array of turtles in turtlesim window; used to find closest turtle to catch
        self.alive_turtles = []      
        self.turtle_sub = self.create_subscription(TurtleArray, "/alive_turtles", self.turtle_callback, 10)

    def p_control_loop(self):
        """P controller implementation to catch closest turtle"""
        if self.alive_turtles and self.state:
            # Closest turtle and P control errors
            catch_turtle, distance_error, theta_error = self.find_closest_turtle()
    
            vel_target = Twist()
            # Check catch threshold
            if distance_error < 0.2:
                # Turtle caught
                self.vel_pub.publish(vel_target)
                self.alive_turtles.remove(catch_turtle)
                self.call_catch_service(catch_turtle.name)
            else:
                # Control signals
                linear_vel = self.k_pos * distance_error
                angular_vel = self.k_theta * theta_error
                # Create velocity message; turtle can only move in x axis in robot frame (forward only)
                vel_target.linear.x = linear_vel
                vel_target.angular.z = angular_vel
                self.vel_pub.publish(vel_target)

    def find_closest_turtle(self):
        """Find closest turtle to catch and P controller errors"""
        catch_turtle = self.alive_turtles[0]
        x_error = catch_turtle.pose[0] - self.state.x
        y_error = catch_turtle.pose[1] - self.state.y
        # Distance from closest turtle
        distance_error = sqrt(x_error**2+y_error**2) 
        for turtle in self.alive_turtles:
            x_check = turtle.pose[0] - self.state.x
            y_check = turtle.pose[1] - self.state.y
            distance_check = sqrt(x_check**2+y_check**2)
            if distance_error > distance_check:
                catch_turtle = turtle
                x_error = x_check
                y_error = y_check
                distance_error = distance_check
        theta_error = atan2(y_error, x_error) - self.state.theta
        # normalize angle
        if theta_error > pi:
            theta_error -= 2*pi
        elif theta_error < -pi:
            theta_error += 2*pi
        return catch_turtle, distance_error, theta_error


    def state_callback(self, state_msg):
        """Update current pose state of turtle1"""
        self.state = state_msg

    def turtle_callback(self, turtle_array_msg):
        """Update available turtles to catch"""
        self.alive_turtles = turtle_array_msg.alive_turtles

    def call_catch_service(self, name):
        """Call catch turtle service with name of turtle to catch"""
        catch_client = self.create_client(CatchTurtle, "/catch_turtle")
        while not catch_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /catch_turtle service...")
        request = CatchTurtle.Request()
        request.name = name
        future = catch_client.call_async(request)
        future.add_done_callback(partial(self.catch_service_callback, name=name))
    
    def catch_service_callback(self, future, name):
        """Catch turtle service callback"""
        try:
            response = future.result()
            self.get_logger().info("Caught {}".format(name))
            # Now change the pen colour !
            pen_client = self.create_client(SetPen, "/turtle1/set_pen")
            while not pen_client.wait_for_service(1.0):
                self.get_logger().warn("waiting for /turtle1/set_pen service...")
            request = SetPen.Request()
            request.r = randint(50, 255)
            request.g = randint(50, 255)
            request.b = randint(50, 255)
            request.width = 4 # Wanna see the colour
            request.off = 0
            future = pen_client.call_async(request)
            future.add_done_callback(self.set_pen_service_callback)
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

    def set_pen_service_callback(self, future):
        """Turtle1 SetPen service callback"""
        try:
            response = future.result()
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

def main(args=None):
    rclpy.init(args=args)
    node = TurtleControlNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()