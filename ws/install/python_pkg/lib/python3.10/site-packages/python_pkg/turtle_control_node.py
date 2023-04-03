import rclpy
from math import atan2, sqrt, pi
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
from interfaces.msg import TurtleArray
from interfaces.srv import CatchTurtle
from functools import partial

class TurtleControlNode(Node):
    """Node to control turtle1 and catch closest turtles. Utilizes a P controller to output velocity targets"""
    def __init__(self):
        super().__init__("turtle_control_node")
        self.get_logger().info("turtle_control_node started...")
        # Pose subscriber; pose state published by turtlesim window
        self.state_sub = self.create_subscription(Pose, "/turtle1/pose", self.state_callback, 10)
        self.state = None

        # P controller loop frequency
        self.control_timer = self.create_timer(0.01, self.p_control_loop)
        # Proportional gains; ratio 1-3 found via testing
        self.k_pos = 2
        self.k_theta = 6

        # Velocity publisher; velocity subscribed to by turtlesim window
        self.vel_pub = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)

        # Array of turtles in turtlesim window; used to find closest turtle to catch
        self.turtle_array = TurtleArray()        
        self.turtle_sub = self.create_subscription(TurtleArray, "/alive_turtles", self.turtle_callback, 10)

    def p_control_loop(self):
        """P controller implementation to catch closest turtle"""
        if self.turtle_array.alive_turtles and self.state:
            # Find closest turtle
            catch_turtle = self.turtle_array.alive_turtles[0]
            x_error = catch_turtle.pose[0] - self.state.x
            y_error = catch_turtle.pose[1] - self.state.y
            distance_error = sqrt(x_error**2+y_error**2)
            for turtle in self.turtle_array.alive_turtles:
                x_check = turtle.pose[0] - self.state.x
                y_check = turtle.pose[1] - self.state.y
                distance_check = sqrt(x_check**2+y_check**2)
                if distance_error > distance_check:
                    catch_turtle = turtle
                    distance_error = distance_check
    
            theta_error = atan2(y_error, x_error) - self.state.theta
            # normalize angle
            if theta_error > pi:
                theta_error -= 2*pi
            elif theta_error < -pi:
                theta_error += 2*pi
            
            vel_target = Twist()
            # Check if close enough to catch
            if distance_error < 0.3:
                # Stop turtle
                self.vel_pub.publish(vel_target)
                self.turtle_array.alive_turtles.remove(catch_turtle)
                self.call_catch_service(catch_turtle.name)
            else:
                # Control signals
                linear_vel = self.k_pos * distance_error
                angular_vel = self.k_theta * theta_error
                # Create velocity message; turtle can only move in x axis in robot frame (forward only)
                vel_target.linear.x = linear_vel
                vel_target.angular.z = angular_vel
                self.vel_pub.publish(vel_target)

    def state_callback(self, state_msg):
        self.state = state_msg

    def turtle_callback(self, turtle_array_msg):
        self.turtle_array = turtle_array_msg

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
        try:
            response = future.result()
            self.get_logger().info("Caught {}".format(name))
        except Exception as e:
            self.get_logger().error("Service call failed: {}".format(e))

def main(args=None):
    rclpy.init(args=args)
    node = TurtleControlNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()