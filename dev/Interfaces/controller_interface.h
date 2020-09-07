#ifndef MODEL_CONTROLLER_INTERFACE_H
#define MODEL_CONTROLLER_INTERFACE_H

#include "../Controller/types.h"
#include "../Model/device.h"

class controller_interfaces {
public:
	class model_interface;
};

class controller_interfaces::model_interface {
public:
	//to model
	static void send_command(Timed_Command timed_command);

	//from model
	static void request_command_add(Timed_Command timed_command);

	//get device pointer from the model
	static Device get_device(Device_Name name);
};

#endif // !MODEL_CONTROLLER_INTERFACE_H