# catching_turtles_ros2

Welcome to my beginner ROS2 project. Please make sure you have ROS2 framework installed on your system to run.
To test program, run "ros2 launch bring_up catching_turtles.launch.py" in root directory.

Two turtlesim windows will pop up. Each window corresponds to code written in C++ or Python (one for each). The main turtle
will try to "catch" all of the turtles randomly spawned in the window. It will do this by catching the closest one. The Python
implementation will have a blue turtle trail and C++ a red one.

Feel free to change the params.yaml file located in ws/src/bring_up/config/ directory. Some parameters include proportional gains used in
P controllers, spawn rate, catch the closest turtle or not, and many more.

Key Technologies:
     - ROS2:
          Topics and Services in C++ and Python,
          Launch files,
          Custom interfaces (data transfer between nodes)
     - Multithreaded processing (C++ only)
     - Object oriented design
     - Client-server model
     - P controller automation
