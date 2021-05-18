# DESCRIPTION ON THE CONTENENT OF THE PACKAGE
This package is composed of four nodes, and three servers. The nodes are go_to_point, user_interface, position_service, state_machine. The servers are Command and RandomPosition and Position.
The node go_to_point implements a server, when it is called it receives a request to reach a point with a given orientation, it then implements the algorithm to control the robot. It reads from the topic /odom the position and the orientation, expressed in quaternions (angle-axis representation) and it publishes to the /cmd_vel topic. The algorithm implemented in the first state orients the robot towards the goal and then it proceeds to move the robot towards the goal in a straight line, when it reaches the goal it starts to rotate to obtain the correct orientation.
The node user_interface reads from input from the client and calls the server that implements the calls to the go_to_point. If the user inserts the number 1 from the keyboard the server is called with request "start", if the user inserts any other character or number the command sent will be "stop" and the robot will stop once the goal is achived.
The node position_service implements a server that receives as input the ranges for the feasible position along x and y and for the feasible orientation and returns a goal position, a point (x;y) and an orientation choosen randomly in the interval.
The node state_machine implements the server for the user_interface client and also implements the client for both the position_server and the go_to_point. It checks if the global variable start is set to true and in that case it calls the server go_to_point. If the user calls the stop command the robot will stop but only once reached the goal. 
This simulations runs on VRep instead of gazebo.

# HOW TO RUN
To run this problem it is necessary to open two terminals: 
In the first terminal go in a ros workspace and run
- roslaunch rt2_assignment1 sim.launch 

In the second terminal make sure to have at least one ros workspace active and to have sourced the correct version of ros. Go in the folder of CoppeliaSim_Edu_V4_2_0_Ubuntu20_04 and run
- ./coppeliaSim.sh

Once the Coppelia Sim Software started in order to open the correct scene go in file, upper left corner, Open scene and select the scene Simulation.ttt

It is really important to run first the ros launch and only after opening VRep.

# ROBOT BEHAVIOUR
The robot starts in the point (0;0) with orientation 0 and velocity zero. It waits for the user command to start the motion. Once the robot starts it goes to the first random position and orientation. If the user calls the stop command the robot will stop as soon as it reaches the goal. If the start command is called again the robot will start moving in towards a new goal. 

# SOFTWARE ARCHITECTURE AND ARCHITECTURAL CHOICES
Two nodes are implemented in language python while two other nodes are implemented in C++. We have a central nodes that communicates with all the others, the state_machine node; it receives commands from the user_interface, it sends a request for a random goal position to the node position_service and another request to the go_to_point.

# SYSTEM'S LIMITATIONS AND POSSIBLE IMPROVMENTS
I noticed that in order to have the requested precision I had to set the velocity of the robot really small, with respect to the ones set with the simulation in Gazebo. In order to be able to have a simulation of acceptable speed it is recommended to speed it up with the hare button. A possible future development could be finding a way of speeding up the robot without loosing precision. I think this could be achived with the proper tuning of the time step and the choice of the robot. 

