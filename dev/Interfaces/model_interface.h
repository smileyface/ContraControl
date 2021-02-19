#ifndef COMMAND_MODEL_INTERFACE
#define COMMAND_MODEL_INTERFACE

#include "../Controller/types.h"
#include "../Controller/Commands/common/initalize.h"
#include "../Model/types.h"
#include "../Model/node/node.h"




class model_interfaces {
public:
	class controller_interface;
};

class model_interfaces::controller_interface {
public:
	static void add_to_step(Model_Command theCommand);
	static void request_command(Model_Command theCommand, double seconds_to_execute);

	static Device* get_device(Node_Id node, Device_Name name);

};

#endif // !MODEL_COMMAND_INTERFACE