#ifndef MODEL_TYPES_H
#define MODEL_TYPES_H

#include "../Controller/Commands/command.h"

#include <string>
typedef std::string Node_Id;
typedef uint16_t Device_Id;
typedef std::pair<Node_Id, Device_Id> Device_Label;
typedef std::string Device_Name;

const uint16_t INVALID_DEVICE = UINT16_MAX;

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
