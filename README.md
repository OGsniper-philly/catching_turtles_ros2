# catching_turtles_ros2

Welcome to my beginner ROS2 project. Please make sure you have ROS2 framework installed on your system to run.
To test program, run "ros2 launch bring_up catching_turtles.launch.py" in root directory.

Two turtlesim windows will pop up. Each window corresponds to code written in C++ or Python (one for each). The main turtle
will try to "catch" all of the turtles randomly spawned in the window. It will do this by catching the closest one. The Python
implementation will have a red turtle trail and C++ a blue one.

Feel free to change the params file located in ws/src/bring_up/config/ directory. You can change the proportional gains used in
the P controller and the spawn rate of the turtles to catch.

Key Technologies:
    ROS2 Topics and Services in C++ and Python
    Custom interfaces for data transfer between nodes
    Multithreaded processing (C++ only)
    Object oriented design
    Client-server model
    P controller automation
