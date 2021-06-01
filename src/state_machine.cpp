#include "ros/ros.h"
#include "rt2_assignment1/Command.h"
#include "rt2_assignment1/RandomPosition.h"
#include <rt2_assignment1/PlanningAction.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

// variable start is needed to know if the user asked to stop or not
bool start = false;
// variable notgoing is used to know when the ther robot is already moving towards a goal or not
bool notgoing = true;

// function that calls the server
bool user_interface(rt2_assignment1::Command::Request &req, rt2_assignment1::Command::Response &res)
	{
		// if the request command is start start is set to true
		if (req.command == "start")
			{
				start = true;
			}
		else 
			{
				// if the command is not start we set start to false
				start = false;
			}
		return true;
}


int main(int argc, char **argv)
{
	// Initialization of the node
	ros::init(argc, argv, "state_machine");
	ros::NodeHandle n;
	ros::NodeHandle n1;
	//initialization of the server
	ros::ServiceServer service= n.advertiseService("/user_interface", user_interface);
	ros::ServiceClient client_rp = n1.serviceClient<rt2_assignment1::RandomPosition>("/position_server");
	actionlib::SimpleActionClient<rt2_assignment1::PlanningAction> ac("/go_to_point");
   
	rt2_assignment1::RandomPosition rp;
	rp.request.x_max = 5.0;
	rp.request.x_min = -5.0;
	rp.request.y_max = 5.0;
	rp.request.y_min = -5.0;
   
	while(ros::ok())
		{
			ros::spinOnce();
			// if the user requested the robot to move
			if (start)
				{
					// if the robot is not moving yet
					if (notgoing)
						{
							// I call for a new goal
							client_rp.call(rp);
							rt2_assignment1::PlanningGoal goal;
							goal.target_pose.header.frame_id = "base_link";
							goal.target_pose.header.stamp = ros::Time::now();
							goal.target_pose.pose.position.x = rp.response.x;
							goal.target_pose.pose.position.y = rp.response.y;
							goal.target_pose.pose.orientation.z = rp.response.theta;
							std::cout << "\nGoing to the position: x= " << rp.response.x << " y= " <<rp.response.y << " theta = " <<rp.response.theta << std::endl;
							ac.sendGoal(goal);
							notgoing = false;
						}
					// if the robot was already moving
					else 
						{
							// I check the status and if the state is SUCCEEDED I set notgoing to true
							if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
								{
									std::cout << "Goal completed" << std::endl;
									notgoing= true;
								}
						}
				}
			// If the user requested the robot to stop
			else 
				{
					// if the robot is already moving towards a goal
					if (!notgoing)
						{
							// I cancel all previous goal and set notgoing to true
							ac.cancelAllGoals();
							std::cout << "Goal cancelled" << std::endl;
							notgoing= true;
						}
				}
  

		}
   return 0;
}
