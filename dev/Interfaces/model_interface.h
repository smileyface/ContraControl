#ifndef COMMAND_MODEL_INTERFACE
#define COMMAND_MODEL_INTERFACE

#include "../Controller/types.h"
#include "../Controller/Commands/common/initalize.h"
#include "../Model/types.h"
#include "../Model/device.h"




class Model_Interfaces {
public:
	class Controller_Interface;
};

class Model_Interfaces::Controller_Interface {
public:
	static void add_to_step(Model_Command theCommand);
	static void request_command(Model_Command theCommand, double seconds_to_execute);

	static Device get_device(Device_Name name);

};

#endif // !MODEL_COMMAND_INTERFACE