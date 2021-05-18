# Research Track 2 - Assignment 1
Inside this file I defined two different classes GoalPositionClient and StateMachine. The class GoalPositionClient is used to implement the client call to the go_to_point server while the StateMachine class implements: the server for the user_interface, the client for the position_server and the timer callback to execute the code periodically, every 500 milliseconds. I implemented it as a component.
## functions for file state_machine.cpp

### void call_serverGTP()
	
Declared in the file state_machine.cpp
	
@brief : This function is called when I want to make a request to the server go_to_point. It calls the server and then wait for the response.
	
### void handle_service(const std::shared_ptr<rmw_request_id_t> request_header, const std::shared_ptr<UserInt::Request> request, const std::shared_ptr<UserInt::Response> response)	

Declare in the file state_machine.cpp

@brief : This function is called when I have a request from the user_interface client. It reads the request and changes the global variable start.

@param : the pointer to the request and response of the server

### void timer_callback()

Declared in the file state_machine.cpp

@brief : This function is executed every 500 milliseconds. It first checks if it is the first execution after reaching a goal, in that case it does nothing, on the other hand if that is not the case it checks the global variable start and if that is set to true it calls the position_server and once it receives a response from that is calls the go_to_point_server.

