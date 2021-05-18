# DESCRIPTION ON THE CONTENENT OF THE PACKAGE
This package is composed of four nodes, two servers and one action. The nodes are go_to_point, user_interface, position_service, state_machine. The servers are Command and RandomPosition. The action is called Planning. 
The node go_to_point implements an action server, when it is called it receives a request to reach a point with a given orientation, it then implements the algorithm to control the robot. It reads from the topic /odom the position and the orientation, expressed in quaternions (angle-axis representation) and it publishes to the /cmd_vel topic. The algorithm implemented in the first state orients the robot towards the goal and then it proceeds to move the robot towards the goal in a straight line, when it reaches the goal it starts to rotate to obtain the correct orientation. If a request to stop is received from the action server the velocity are set to zero and the action server is set to preempted and so it is stopped.
The node user_interface reads from input from the client and calls the server that implements the calls to the go_to_point. If the user inserts the number 1 from the keyboard the server is called with request "start", if the user inserts any other character or number the command sent will be "stop" and the robot will stop immediately, it will not wait to reach the goal.
The node position_service implements a server that receives as input the ranges for the feasible position along x and y and for the feasible orientation and returns a goal position, a point (x;y) and an orientation choosen randomly in the interval.
The node state_machine implements the server for the user_interface client and also implements the client for both the position_server and the go_to_point. It checks if the global variable start is set to true and in that case, if it is the first time the variable was set to true the position_service is called and after that the response is set as request for the go_to_point server. If on the other hand the variable is true but not for the first time it is only checked if the action server has succeeded. If the variable start is set to stop while the robot is moving then a cancel all goals request is sent to the action server. If the request stop is sent but the robot is not moving nothing is done. Once the goal position is reached if the global variable start is still true a new goal position will be requested.

# HOW TO RUN
To run this problem it is necessary to open a terminal in a ros workspace and run 
- roslaunch rt2_assignment1 sim.launch

# ROBOT BEHAVIOUR
The robot starts in the point (0;0) with orientation 0 and velocity zero. It waits for the user command to start the motion. Once the robot starts it goes to the first random position and orientation. If the user calls the stop command the robot stops and cancels the previous goals. If the start command is called again the robot will start moving towards a new goal. 

# SOFTWARE ARCHITECTURE AND ARCHITECTURAL CHOICES
Two nodes are implemented in language python while two other nodes are implemented in C++. We have a central node that communicates with all the others, the state_machine node; it receives commands from the user_interface, it sends a request for a random goal position to the node position_service and another request to the go_to_point.

# SYSTEM'S LIMITATIONS AND POSSIBLE IMPROVMENTS
A system possibile limitation might be the fact that when the user asks to stop the robot there is not the possibility to choose wheater to cancel the goal or to just stop the motion and retrieve the goal later. To implement this we would need two different commands for the stop, and we would need to save the previous goal in a variable to send the goal again when the start command is sent. 

