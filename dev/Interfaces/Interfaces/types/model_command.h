#ifndef INTERFACE_MODEL_COMMAND_TYPE
#define INTERFACE_MODEL_COMMAND_TYPE

#include <string>
#include <vector>

#include "Interfaces/types/device_label.h"
#include "../../../Controller/commands.h"

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

typedef std::vector<Model_Command> Command_List;

#endif // !INTERFACE_MODEL_COMMAND_TYPE


