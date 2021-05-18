# DESCRIPTION ON THE CONTENENT OF THE PACKAGE
Inside this repository I have two packages and 4 scripts. The packages are called rt2_assignement and rt2_assignment1. 
The package rt2_assignment is implemented with the software ROS noetic. The package rt2_assignment1 on the other hand is developed with software ROS2 foxy. I need to have the package rt2_assignment in a ros noetic workspace and the other in a ros2 foxy workspace.
In order to be able to execute this program it is needed to have installed in the ros2 foxy workspace the ros1_bridge package. This package can be downloaded from https://github.com/ros2/ros1_bidge
The four scripts are called ros.sh, ros2.sh, ros12.sh and script.sh. 
Inside the package rt2_assignment I implemented two nodes go_to_point.py and user_interface.py. The node go_to_point implements the server that allows the robot to reach a goal position by first rotating in order to direct the robot towards the goal position, after that it will move in a straight line to the goal and once that is reached it will rotate to obtain the goal orientation.
The user_interface implements a client that reads the input from the keyboard and send the command start or stop to the server inside the node state_machine.
Inside the package rt2_assignment1 I have two components: the position_service and the state_machine; I also have the mapping_rule.yaml file. The mapping_rule is needed in order to guarantee the communication between the two packages in ros noetic and ros2 foxy. The position_service is called by the state_machine when it is needed to generate another goal position. It takes as input the feasible ranges of x and y and it returns a random position and orientation for the robot. The component state_machine on the other hand implements the control of the robot, it waits for the start command and once that is received it calls the position_service and inside the call, when a response is received it will also call the go_to_point server that is implemented in ros.
The script script.sh is used to run the entire program in both ros noetic and ros foxy. It will open three different terminals, one in ros noetic, one that can run both the ros noetic and the ros foxy and one that runs the ros foxy. In the first terminal the script ros.sh is executed, inside that script it is sourced the ros noetic workspace. Still in the first terminal it is then called the launch file to run gazebo and the two nodes inside the package rt2_assignment. In the second terminal both workspaces will be sourced and after that it will run the ros bridge that will allow for the communication between the two packages. On the last terminal it is sourced the ros2 workspace and it is run the launchfile that starts the container and the two components.

# HOW TO RUN
In order to run this program you must have in your root folder the 4 scripts and you should have your workspace for ros noetic called my_ros and the workspace for ros2 foxy called my_ros2. If that is not the case it is necessary to change the scripts ros.sh, ros12.sh and ros2.sh.
To start the simulation run:
- source script.sh

To compile the simulation: 
inside the ros noetic workspace run:
- catkin_make
Inside the ros2 foxy workspace run to build only the package:
- colcon build --symlink-install --packages-skip ros1_bridge
Inside the ros2 foxy workspace run to build only the bridge:
- colcon build --packages-select ros1_bridge --cmake-force-configure


# ROBOT BEHAVIOUR
The robot starts in the point (0;0) with orientation 0 and velocity zero. It waits for the user command to start the motion. Once the robot starts it goes to the first random position and orientation. If the user calls the stop command the robot stops and cancels the previous goals. If the start command is called again the robot will start moving in towards a new goal. If the robot reaches the goal position and the stop command has not been called it will automatically request a new goal position and it will reach that one too.

# SOFTWARE ARCHITECTURE AND ARCHITECTURAL CHOICES
This program is implemented in both ros noetic and ros2 foxy. In particular we have two nodes, written in python, in ros noetic and two components, written in cpp, in ros2 foxy. We have a central node, state_machine that communicates with all the other nodes, it is a server for user_interface and also it is a client for both the node go_to_point and the position_service. In order to implement the communication between these nodes it is needed the package ros1_bridge. 

# SYSTEM'S LIMITATIONS AND POSSIBLE IMPROVMENTS
A possible problem of this code is that I noticed that after serving a position request, even if the command stop was called the robot would serve another request. In order to avoid this I used a global variable that is set to true when the robot reaches a goal position, when starting a new call of the timer_callback I check if that global variable is set to true and in that case I do nothing for one cycle. This can waste time and would not be ideal in real time situation. A possible further implementation could be trying to avoid this behaviour.


