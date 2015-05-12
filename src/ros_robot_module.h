/*
* File: ROSrobot_module.h
* Author: m79lol, iskinmike
*
*/
#ifndef ROS_ROBOT_MODULE_H
#define	ROS_ROBOT_MODULE_H
class ROSRobot : public Robot {
public:
	int robot_index;

	std::vector<variable_value> axis_state;
	ROSRobot(int robot_index) : robot_index(0){};
	FunctionResult* executeFunction(system_value command_index, void **args);
	void axisControl(system_value axis_index, variable_value value);
	~ROSRobot() {};
};

typedef std::vector<ROSRobot*> m_connections;

class ROSRobotModule : public RobotModule{
	CRITICAL_SECTION VRM_cs;
	m_connections aviable_connections;
	FunctionData **ROSrobot_functions;
	AxisData **robot_axis;
	colorPrintf_t *colorPrintf;

public:
	ROSRobotModule();

	//init
	const char *getUID();
	void prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p);

	//compiler only
	FunctionData** getFunctions(unsigned int *count_functions);
	AxisData** getAxis(unsigned int *count_axis);
	void *writePC(unsigned int *buffer_length);

	//intepreter - devices
	int init();
	Robot* robotRequire();
	void robotFree(Robot *robot);
	void final();

	//intepreter - program
	int startProgram(int uniq_index, void *buffer, unsigned int buffer_length);
	int endProgram(int uniq_index);

	//destructor
	void destroy();
	~ROSRobotModule(){};
};
#endif	/* ROS_ROBOT_MODULE_H */