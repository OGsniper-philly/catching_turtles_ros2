#include "cpp_pkg/turtle_control_node.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

TurtleControlNode::TurtleControlNode()
    : Node("turtle_control_node"), k_linear_{3}, k_theta_{10}
{
    control_timer_ = this->create_wall_timer(1ms, std::bind(&TurtleControlNode::p_control_loop, this));
    state_sub_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10,
                                                                 std::bind(&TurtleControlNode::state_subscription_callback, this, _1));
    velocity_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    turtles_sub_ = this->create_subscription<interfaces::msg::TurtleArray>("/alive_turtles", 10,
                                                                           std::bind(&TurtleControlNode::turtles_subscription_callback, this, _1));
}

void TurtleControlNode::p_control_loop()
{
    if (!alive_turtles_.empty())
    {
        auto closest_turtle = find_closest_turtle();
        double x_error = closest_turtle.pose[0] - state_.x;
        double y_error = closest_turtle.pose[1] - state_.y;
        // P control errors
        double distance_error = sqrt(x_error * x_error + y_error * y_error);
        double theta_error = atan2(y_error, x_error) - state_.theta;
        // normalize angle
        if (theta_error > M_PI)
        {
            theta_error -= 2 * M_PI;
        }
        else if (theta_error < -M_PI)
        {
            theta_error += 2 * M_PI;
        }

        geometry_msgs::msg::Twist velocity_msg{};
        if (distance_error < 0.2)
        {
            velocity_pub_->publish(velocity_msg);
            auto itr = std::find(alive_turtles_.begin(), alive_turtles_.end(), closest_turtle);
            alive_turtles_.erase(itr);
            client_threads_.push_back(std::thread(std::bind(&TurtleControlNode::call_catch_service, this, closest_turtle.name)));
        }
        else
        {
            // Control signal
            velocity_msg.linear.x = distance_error * k_linear_;
            velocity_msg.angular.z = theta_error * k_theta_;
            velocity_pub_->publish(velocity_msg);
        }
        return;
    }
}

void TurtleControlNode::call_catch_service(const std::string &name)
{
    auto catch_client = create_client<interfaces::srv::CatchTurtle>("/catch_turtle");
    while (!catch_client->wait_for_service(1s))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for /catch_turtle service ...");
    }
    auto request = std::make_shared<interfaces::srv::CatchTurtle::Request>();
    request->name = name;
    auto future = catch_client->async_send_request(request);

    try
    {
        auto response = future.get();
        RCLCPP_WARN(this->get_logger(), std::string(std::string("Caught ")+name).c_str());
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(this->get_logger(), e.what());
    }
    return;
}

void TurtleControlNode::turtles_subscription_callback(const interfaces::msg::TurtleArray &turtles)
{
    alive_turtles_ = turtles.alive_turtles;
    RCLCPP_INFO(this->get_logger(), "Available to catch:");
    for (auto &turtle : alive_turtles_)
    {
        RCLCPP_INFO(this->get_logger(), std::string(std::string("   ")+turtle.name).c_str());
    }
    return;
}

interfaces::msg::Turtle TurtleControlNode::find_closest_turtle()
{
    assert(!alive_turtles_.empty());
    auto closest_turtle = alive_turtles_[0];
    for (const auto &turtle : alive_turtles_)
    {
        double distance = sqrt((closest_turtle.pose[0]-state_.x) * (closest_turtle.pose[0]-state_.x) + (closest_turtle.pose[1]-state_.y)* (closest_turtle.pose[1]-state_.y));
        double check = sqrt((turtle.pose[0]-state_.x) * (turtle.pose[0]-state_.x) + (turtle.pose[1]-state_.y) * (turtle.pose[1]-state_.y));
        if (check < distance)
        {
            closest_turtle = turtle;
        }
    }
    return closest_turtle;
}

void TurtleControlNode::state_subscription_callback(const turtlesim::msg::Pose &pose_msg)
{
    state_ = pose_msg;
    return;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
