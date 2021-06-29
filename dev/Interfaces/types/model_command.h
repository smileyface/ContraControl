#ifndef INTERFACE_MODEL_COMMAND_TYPE
#define INTERFACE_MODEL_COMMAND_TYPE
#include "../../Interfaces/types/device_label.h"
#include "../../Controller/commands.h"
class Model_Command {
public:
	Model_Command(Device_Label device_label, Command* cmd)
	{
		label = device_label;
		command = cmd;
	};
	Device_Label label;
	Command* command;
};

#endif // !INTERFACE_MODEL_COMMAND_TYPE


