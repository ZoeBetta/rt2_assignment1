# Research Track 2 - Assignment 1

## functions for file go_to_point.py

### clbk_odom(msg)

Defined in the file go_to_point.py

 @brief : It is called every time I have new data on the topic /odom. Once this function is called it will save the data on a global variable and it will also convert the quaternion data on euler angles format. The Euler angle yaw will be saved on a global variable.
 
 @param : msgs - a message in the format nav_msgs/Odometry, we use the fields; pose.pose.position.x, pose.pose.position.y and pose.pose.orientation.x, pose.pose.orientation.y, pose.pose.orientation.z, pose.pose.orientation.w.

### change_state(state)

Defined in the file go_to_point.py

@brief : this function is called to change the value of the variable state, it will also print the new state.

@param : state - It receives as input the new state

### normalize_angle(angle)

Defined in the file go_to_point.py

@brief : this function normalizes the angle received as input. It will put the angle in the interval [-pi;pi]

@param : angle - It receives as input the angle that needs to be normalized

### fix_yaw(des_pos)

Defined in the file go_to_point.py

@brief : This function calculates the error of orientation with respectof the final orientation needed to reach the goal while going in a straight line. It then sets the angular velocity to reach that orientation. After setting the velocity it is checked if the error is below a given threshold and if that is the case the state is changed. 

@param : des_pos - The goal position, in particular the x and y coordinates

### go_straight_ahead(des_pos)

Defined in the file go_to_point.py

@brief : It makes the robot go in a straight line, the position error and the orientation error. Depending on those the linear velocity and the angular velocity are set. If the robot has the position error below a given threshold the state is changed. It is also checked the error on the orientation to reach the goal and if that is greater than a threshold the state is changed to the previous one

@param : des_pos - The goal position, in particular the x and y coordinates

### fix_final_yaw(des_yaw)

Defined in the file go_to_point.py

@brief : It is calculated the error between the actual orientation and the goal orientation. Depending on the magnitude of the error the angular velocity is published. If the error is below a given threshold the state is changed to the final state.

@param : des_yaw - the goal orientation, expressed in yaw angle (euler)

### done()

Defined in the file go_to_point.py

@brief : This function implements the last state of the go_to_point algorithm. It stops all the velocity putting them to zero and it sets the action server to succeeded. 


### go_to_point(goal)

Defined in the file go_to_point.py

@brief : it retrieves the desired position and orientation. It is first checked if the action is preempted and if that is the case all the velocity are set to zero and the action is set preempted. It then checks the state and depending on it it calls the corresponding function. 

@param : goal - It is the request the action server receives. It contains goal position and orientation

