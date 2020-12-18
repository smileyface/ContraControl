#ifndef MODEL_CONTROLLER_INTERFACE_H
#define MODEL_CONTROLLER_INTERFACE_H

#include "../Controller/types.h"
#include "../Model/device.h"

class Controller_Interfaces {
public:
	class Model_Interface;

};

class Controller_Interfaces::Model_Interface {
public:
	//to model
	static void send_command(Timed_Command timed_command);

	//from model
	static void request_command_add(Timed_Command timed_command);

	//get device pointer from the model
	static Device get_device_from_model(Device_Name name);
};

#endif // !MODEL_CONTROLLER_INTERFACE_H