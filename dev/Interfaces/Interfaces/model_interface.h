#ifndef COMMAND_MODEL_INTERFACE
#define COMMAND_MODEL_INTERFACE

#include "types/model_command.h"
#include "../Model/device.h"




class Model_Interfaces {
public:
	class Controller_Interface;
};

class Model_Interfaces::Controller_Interface {
public:
	static void add_to_step(Model_Command theCommand);
	static void request_command(Model_Command theCommand, double seconds_to_execute);

	static Device* get_device(Node_Id node, Device_Name name);

};

#endif // !MODEL_COMMAND_INTERFACE