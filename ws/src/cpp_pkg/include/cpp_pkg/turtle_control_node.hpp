#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "interfaces/msg/turtle_array.hpp"
#include "interfaces/msg/turtle.hpp"
#include "interfaces/srv/catch_turtle.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <vector>
#include <utility>

using namespace std::chrono_literals;
using std::placeholders::_1;

class TurtleControlNode : public rclcpp::Node
{
    public:
        TurtleControlNode();
        void p_control_loop();
        void state_subscription_callback(const turtlesim::msg::Pose &pose_msg);
        void turtles_subscription_callback(const interfaces::msg::TurtleArray &turtles);
        void call_catch_service(const std::string &name);
        interfaces::msg::Turtle find_closest_turtle();
    private:
        int16_t k_linear_;
        int16_t k_theta_;
        rclcpp::TimerBase::SharedPtr control_timer_;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr state_sub_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_pub_;
        turtlesim::msg::Pose state_;
        rclcpp::Subscription<interfaces::msg::TurtleArray>::SharedPtr turtles_sub_;
        std::vector<interfaces::msg::Turtle> alive_turtles_;
        std::vector<std::thread> client_threads_;
};