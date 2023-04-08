cmake_minimum_required(VERSION 3.8)
project(cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(interfaces REQUIRED) 

include_directories(include)

add_executable(turtle_control_node src/turtle_control_node.cpp)
ament_target_dependencies(turtle_control_node rclcpp turtlesim geometry_msgs interfaces)

add_executable(turtle_spawner_node src/turtle_spawner_node.cpp)
ament_target_dependencies(turtle_spawner_node rclcpp turtlesim interfaces)

install(TARGETS
  turtle_control_node
  turtle_spawner_node
  DESTINATION lib/${PROJECT_NAME}
  )

ament_package()
