#include "cpp_pkg/turtle_spawner_node.hpp"

TurtleSpawnerNode::TurtleSpawnerNode()
    : Node("turtle_spawner_node")
{
    this->declare_parameter("spawn_frequency", 1);
    spawn_frequency_ = this->get_parameter("spawn_frequency").as_int();
    spawn_timer_ = this->create_wall_timer(std::chrono::seconds(1/spawn_frequency_), std::bind(&TurtleSpawnerNode::spawn_timer_callback, this));
    turtles_pub_ = this->create_publisher<interfaces::msg::TurtleArray>("/alive_turtles", 10);
    catch_service_ = this->create_service<interfaces::srv::CatchTurtle>("/catch_turtle", std::bind(&TurtleSpawnerNode::catch_service_callback, this, _1, _2));
    // TODO: GET NAME PARAMETER
    RCLCPP_INFO(this->get_logger(), "turtle_spawner_node started ...");
}

void TurtleSpawnerNode::catch_service_callback(interfaces::srv::CatchTurtle::Request::SharedPtr request, interfaces::srv::CatchTurtle::Response::SharedPtr response)
{
    client_threads_.push_back(std::thread(std::bind(&TurtleSpawnerNode::call_kill_service, this, request->name)));
    response = std::make_shared<interfaces::srv::CatchTurtle::Response>();
    return;
}

void TurtleSpawnerNode::call_kill_service(const std::string &name)
{
    auto kill_client = create_client<turtlesim::srv::Kill>("/kill");
    while (!kill_client->wait_for_service(1s))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for /kill service ...");
    }
    auto request = std::make_shared<turtlesim::srv::Kill::Request>();
    request->name = name;
    auto future = kill_client->async_send_request(request);

    try
    {
        auto response = future.get();
        for (std::vector<interfaces::msg::Turtle>::iterator itr = alive_turtles_.begin(); itr < alive_turtles_.end(); itr++)
        {
            if (itr->name == request->name)
            {
                alive_turtles_.erase(itr);
                break;
            }
        }
        RCLCPP_WARN(this->get_logger(), std::string(std::string("Killed ") + name).c_str());
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), e.what());
    }
    return;
}

void TurtleSpawnerNode::spawn_timer_callback()
{
    client_threads_.push_back(std::thread(std::bind(&TurtleSpawnerNode::call_spawn_service, this)));
    return;
}

void TurtleSpawnerNode::call_spawn_service()
{
    auto spawn_client = this->create_client<turtlesim::srv::Spawn>("/spawn");
    while (!spawn_client->wait_for_service(1s))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for /spawn service ...");
    }
    static std::default_random_engine engine;
    std::uniform_real_distribution<float> position(0.5, 10.5);
    std::uniform_real_distribution<float> angle(0.0, 2 * M_PI);
    auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
    request->x = position(engine);
    request->y = position(engine);
    request->theta = angle(engine);
    auto future = spawn_client->async_send_request(request);
    try
    {
        auto response = future.get();
        interfaces::msg::Turtle new_turtle;
        new_turtle.pose[0] = request->x;
        new_turtle.pose[1] = request->y;
        new_turtle.pose[2] = request->theta;
        new_turtle.name = response->name;
        alive_turtles_.push_back(new_turtle);
        interfaces::msg::TurtleArray turtles;
        turtles.alive_turtles = alive_turtles_;
        turtles_pub_->publish(turtles);
        RCLCPP_INFO(this->get_logger(), std::string(std::string("Spawned ") + response->name).c_str());
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), e.what());
    }
    return;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawnerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
