import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist

class TurtleControlNode(Node):
    def __init__(self):
        super().__init__("turtle_control_node")
        self.get_logger().info("turtle_control_node started...")
        self.state_sub = self.create_subscription(Pose, "/turtle1/pose", self.state_callback, 10)
        self.vel_pub = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)


    def state_callback(self, state_msg):
        pass

def main(args=None):
    rclpy.init(args=args)
    node = TurtleControlNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()