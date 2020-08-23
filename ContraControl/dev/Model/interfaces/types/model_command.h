#ifndef MODEL_COMMAND_TYPE
#define MODEL_COMMAND_TYPE

#include "../../../Controller/Commands/command.h"
#include "../../device.h"

class Model_Command {
	public:
		Model_Command(Device_Id device_id, Command* cmd) 
		{ 
			id = device_id; 
			command = cmd; 
		};
	Device_Id id;
	Command* command;
};

#endif