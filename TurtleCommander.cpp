#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

#include <beginner_tutorials/Spawn.h>
#include <beginner_tutorials/Kill.h>

#include <string>

// GLOBAL VARIABLES
ros::Rate *ploop_rate ;
ros::NodeHandle *pNode;
//

void initTurtles()
{
	// proxy args for ros::init()
	int targ1=1;
	char ch1[6]="proxy";
	char *pch1=ch1;
	char **targ2=&pch1;
	/////////////////////////////
	
	if (!ros::isInitialized()){
		ros::init(targ1, targ2, "TurtleCommander");
	}
	
	ros::NodeHandle *n = new ros::NodeHandle;
	ros::Rate *loop_rate = new ros::Rate(2);
	
	pNode = n;
	ploop_rate = loop_rate;
}

void clearTurtleNode()
{
	delete pNode;
	delete ploop_rate;
}


std::string spawnTurtle(double x, double y, double theta, std::string name)
{
	ros::ServiceClient turtle_spawn_int = (*pNode).serviceClient<beginner_tutorials::Spawn>("spawn",1);

	beginner_tutorials::Spawn newTurtle;
	
	newTurtle.request.x=x;
	newTurtle.request.y=y;
	newTurtle.request.theta=theta;
	newTurtle.request.name=name;
	
	turtle_spawn_int.call(newTurtle);

	return newTurtle.response.name;
}


void killTurtle(std::string name)
{
	beginner_tutorials::Kill turtle;
	turtle.request.name = name;
	ros::ServiceClient turtle_kill_int = (*pNode).serviceClient<beginner_tutorials::Kill>("kill",1);
	turtle_kill_int.call(turtle);
}


void moveTurtle(std::string name, double ForwardSpeed, double AngularSpeed)
{
	ros::Publisher chatter_pub_int = (*pNode).advertise<geometry_msgs::Twist>(name + "/cmd_vel", 1000);
	geometry_msgs::Twist MesToTurtle;
	
	MesToTurtle.linear.x = ForwardSpeed;
	MesToTurtle.angular.z = AngularSpeed;
	
	(*ploop_rate).sleep();
	chatter_pub_int.publish(MesToTurtle);
	
	ros::spinOnce();
	(*ploop_rate).sleep();
}
void moveTurtleForward(std::string name, double ForwardSpeed)
{
	ros::Publisher chatter_pub_int = (*pNode).advertise<geometry_msgs::Twist>(name + "/cmd_vel", 1000);

	geometry_msgs::Twist MesToTurtle;
	
	MesToTurtle.linear.x = ForwardSpeed;
	MesToTurtle.angular.z = 0;
	
	(*ploop_rate).sleep();
	chatter_pub_int.publish(MesToTurtle);
	
	ros::spinOnce();
	(*ploop_rate).sleep();
}
void rotateTurtle(std::string name, double AngularSpeed)
{
	ros::Publisher chatter_pub_int = (*pNode).advertise<geometry_msgs::Twist>(name + "/cmd_vel", 1000);

	geometry_msgs::Twist MesToTurtle;
	
	MesToTurtle.linear.x = 0;
	MesToTurtle.angular.z = AngularSpeed;
	
	(*ploop_rate).sleep();
	chatter_pub_int.publish(MesToTurtle);
	
	ros::spinOnce();
	(*ploop_rate).sleep();
}
