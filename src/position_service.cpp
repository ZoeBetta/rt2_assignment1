#include "ros/ros.h"
#include "rt2_assignment1/RandomPosition.h"

// funtion to obtain a random number between a minimum and a maximum
double randMToN(double M, double N)
{     return M + (rand() / ( RAND_MAX / (N-M) ) ) ; }

// function called when we have a request from the client
bool myrandom (rt2_assignment1::RandomPosition::Request &req, rt2_assignment1::RandomPosition::Response &res){
    res.x = randMToN(req.x_min, req.x_max);
    res.y = randMToN(req.y_min, req.y_max);
    res.theta = randMToN(-3.14, 3.14);
    return true;
}


int main(int argc, char **argv)
{
	// initialization of the node
   ros::init(argc, argv, "random_position_server");
   ros::NodeHandle n;
   // initialization of the server
   ros::ServiceServer service= n.advertiseService("/position_server", myrandom);
   ros::spin();

   return 0;
}
