
#include <time.h>
#include <vector>

#include "../module_headers/module.h"
#include "../module_headers/robot_module.h"
#include "../module_headers/function_module.h"

#include "ros_robot_module.h"
#include "SimpleIni.h"

#include "ros_messages.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

/////////
const unsigned int COUNT_ROSRobot_FUNCTIONS = 5;
const unsigned int COUNT_AXIS = 0;

ROSRobotModule::ROSRobotModule() {
	ROSrobot_functions = new FunctionData*[COUNT_ROSRobot_FUNCTIONS];
	system_value function_id = 0;

	FunctionData::ParamTypes *Params = new FunctionData::ParamTypes[6];
	Params[0] = FunctionData::FLOAT;
	Params[1] = FunctionData::FLOAT;
	Params[2] = FunctionData::FLOAT;
	Params[3] = FunctionData::FLOAT;
	Params[4] = FunctionData::FLOAT;
	Params[5] = FunctionData::STRING;

	ROSrobot_functions[function_id] = new FunctionData(function_id + 1, 6, Params, "spawn");
	function_id++;


	Params = new FunctionData::ParamTypes[3];
	Params[0] = FunctionData::FLOAT;
	Params[1] = FunctionData::FLOAT;
	Params[2] = FunctionData::FLOAT;

	ROSrobot_functions[function_id] = new FunctionData(function_id + 1, 3, Params, "move");
	function_id++;


	Params = new FunctionData::ParamTypes[1];
	Params[0] = FunctionData::STRING;

	ROSrobot_functions[function_id] = new FunctionData(function_id + 1, 1, Params, "changeColor");
	function_id++;


	ROSrobot_functions[function_id] = new FunctionData(function_id + 1, 0, NULL, "getX");
	function_id++;
	ROSrobot_functions[function_id] = new FunctionData(function_id + 1, 0, NULL, "getY");
};



FunctionData** ROSRobotModule::getFunctions(unsigned int *count_functions) {
	*count_functions = COUNT_ROSRobot_FUNCTIONS;
	return ROSrobot_functions;
}



Robot* ROSRobotModule::robotRequire(){
	EnterCriticalSection(&VRM_cs);
	ROSRobot *ROS_robot = new ROSRobot(0);
	aviable_connections.push_back(ROS_robot);

	Robot *robot = ROS_robot;
	LeaveCriticalSection(&VRM_cs);
	return robot;
};


void ROSRobotModule::robotFree(Robot *robot){
	EnterCriticalSection(&VRM_cs);
	ROSRobot *ROS_robot = reinterpret_cast<ROSRobot*>(robot);
	for (m_connections::iterator i = aviable_connections.begin(); i != aviable_connections.end(); ++i) {
		if (ROS_robot == *i){
			if ((*i)->robot_index){
				//deleteRobot((*i)->robot_index);
			};
			delete (*i);
			aviable_connections.erase(i);
			break;
		};
	}
	LeaveCriticalSection(&VRM_cs);
};


void ROSRobotModule::final(){
	aviable_connections.clear();
};

void ROSRobotModule::destroy() {
	for (unsigned int j = 0; j < COUNT_ROSRobot_FUNCTIONS; ++j) {
		delete ROSrobot_functions[j];
	}
	delete[] ROSrobot_functions;
	delete this;
};

AxisData **ROSRobotModule::getAxis(unsigned int *count_axis){
	count_axis = COUNT_AXIS;
	return NULL;
};

void ROSRobot::axisControl(system_value axis_index, variable_value value){
};

void *ROSRobotModule::writePC(unsigned int *buffer_length) {
	*buffer_length = 0;
	return NULL;
}




void ROSRobotModule::prepare(colorPrintf_t *colorPrintf_p, colorPrintfVA_t *colorPrintfVA_p) {
	colorPrintf = colorPrintf_p;
}

const char* ROSRobotModule::getUID() {
	return "ROSRobot_functions_dll";
};






FunctionResult* ROSRobot::executeFunction(system_value functionId, void **args) {
	if ((functionId < 1) || (functionId > COUNT_ROSRobot_FUNCTIONS)) {
		return NULL;
	}
	variable_value rez = 0;
	try {
		switch (functionId) {
		case 1: {

			break;
		}
		case 2: {

			break;
		}
		case 3: {

			break;
		}
		case 4: {

			break;
		}
		case 5: {

			break;
		}
		};
		return new FunctionResult(1, rez);
	}
	catch (...){
		return new FunctionResult(0);
	};
};




int ROSRobotModule::startProgram(int uniq_index, void *buffer, unsigned int buffer_length) {
	return 0;
}

int ROSRobotModule::endProgram(int uniq_index) {
	return 0;
}


__declspec(dllexport) RobotModule* getRobotModuleObject() {
	return new ROSRobotModule();
};