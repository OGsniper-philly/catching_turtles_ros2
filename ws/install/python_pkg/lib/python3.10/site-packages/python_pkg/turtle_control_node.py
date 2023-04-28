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
    def __init__(self):
        super().__init__("turtle_control_node")
        self.declare_parameter("k_linear", 3.0)
        self.declare_parameter("k_theta", 7.0)
        self.declare_parameter("catch_closest_turtle", True)
        self.k_linear = self.get_parameter("k_linear").get_parameter_value().double_value
        self.k_theta = self.get_parameter("k_theta").get_parameter_value().double_value
        self.catch_closest_turtle = self.get_parameter("catch_closest_turtle").get_parameter_value().bool_value

        self.state_sub = self.create_subscription(Pose, "/turtle1/pose", self.state_callback, 10)
        self.state = Pose()

        self.control_timer = self.create_timer(0.01, self.p_control_loop)

        self.vel_pub = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)

        self.alive_turtles = []      
        self.turtle_sub = self.create_subscription(TurtleArray, "/alive_turtles", self.turtle_callback, 10)

        self.call_set_pen_service()

        self.get_logger().info("turtle_control_node started...")


    def p_control_loop(self):
        if self.alive_turtles:
            if self.catch_closest_turtle:
                closest_turtle = self.find_closest_turtle()
            else:
                closest_turtle = self.alive_turtles[0]
            x_error = closest_turtle.pose[0] - self.state.x
            y_error = closest_turtle.pose[1] - self.state.y
            distance_error = sqrt(x_error**2+y_error**2)
            theta_error = atan2(y_error, x_error) - self.state.theta
            if theta_error > pi:
                theta_error -= 2*pi
            elif theta_error< -pi:
                theta_error += 2*pi
    
            vel_target = Twist()
            if distance_error < 0.4:
                self.vel_pub.publish(vel_target)
                self.alive_turtles.remove(closest_turtle)
                self.call_catch_service(closest_turtle.name)
            else:
                linear_vel = self.k_linear * distance_error
                angular_vel = self.k_theta * theta_error
                vel_target.linear.x = linear_vel
                vel_target.angular.z = angular_vel
                self.vel_pub.publish(vel_target)

    def find_closest_turtle(self):
        closest_turtle = self.alive_turtles[0]
        x_error = closest_turtle.pose[0] - self.state.x
        y_error = closest_turtle.pose[1] - self.state.y
        distance_error = sqrt(x_error**2+y_error**2) 
        for turtle in self.alive_turtles:
            x_check = turtle.pose[0] - self.state.x
            y_check = turtle.pose[1] - self.state.y
            distance_check = sqrt(x_check**2+y_check**2)
            if distance_error > distance_check:
                closest_turtle = turtle
                distance_error = distance_check
        return closest_turtle

    def state_callback(self, state_msg):
        self.state = state_msg

    def turtle_callback(self, turtle_array_msg):
        self.alive_turtles = turtle_array_msg.alive_turtles
        self.get_logger().info("Available to catch:")
        for turtle in self.alive_turtles:
            self.get_logger().info("\t"+turtle.name)

    def call_catch_service(self, name):
        catch_client = self.create_client(CatchTurtle, "/catch_turtle")
        while not catch_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /catch_turtle service...")
        request = CatchTurtle.Request()
        request.name = name
        future = catch_client.call_async(request)
        future.add_done_callback(partial(self.catch_service_callback, name=name))
    
    def catch_service_callback(self, future, name):
        try:
            response = future.result()
            self.get_logger().info("Caught {}".format(name))
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

    def call_set_pen_service(self):
        pen_client = self.create_client(SetPen, "/turtle1/set_pen")
        while not pen_client.wait_for_service(1.0):
            self.get_logger().warn("waiting for /turtle1/set_pen service...")
        request = SetPen.Request()
        request.r = 255
        request.width = 4
        future = pen_client.call_async(request)
        future.add_done_callback(self.set_pen_service_callback)

    def set_pen_service_callback(self, future):
        try:
            response = future.result()
            self.get_logger().info("Set pen to red.")
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

def main(args=None):
    rclpy.init(args=args)
    node = TurtleControlNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()