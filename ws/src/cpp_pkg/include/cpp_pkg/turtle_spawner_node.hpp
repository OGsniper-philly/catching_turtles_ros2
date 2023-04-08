#include "rclcpp/rclcpp.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
#include "interfaces/msg/turtle.hpp"
#include "interfaces/msg/turtle_array.hpp"
#include "interfaces/srv/catch_turtle.hpp"

#include <vector>
#include <random>

using namespace std::chrono_literals;

using std::placeholders::_1;
using std::placeholders::_2;

class TurtleSpawnerNode : public rclcpp::Node
{
public:
    TurtleSpawnerNode();
    void spawn_timer_callback();
    void call_spawn_service();
    void catch_service_callback(interfaces::srv::CatchTurtle::Request::SharedPtr request, interfaces::srv::CatchTurtle::Response::SharedPtr response);
    void call_kill_service(const std::string &name);

private:
    rclcpp::TimerBase::SharedPtr spawn_timer_;
    std::vector<std::thread> client_threads_;
    std::vector<interfaces::msg::Turtle> alive_turtles_;
    rclcpp::Publisher<interfaces::msg::TurtleArray>::SharedPtr turtles_pub_;
    rclcpp::Service<interfaces::srv::CatchTurtle>::SharedPtr catch_service_;
};
