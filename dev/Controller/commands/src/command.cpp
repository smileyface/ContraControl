#include "../command.h"

Command::Command() : 
	complete(false)
{ }


COMMAND_ENUM Command::get_id() 
{ 
	return COMMAND_ENUM::INVALID; 
}

bool Command::completed() 
{ 
	return complete;
}

void Command::complete_command()
{
	complete = true;
}

std::string Command::get_id_str()
{
	std::string value("Invalid");
	switch(get_id())
	{
	case COMMAND_ENUM::ASSIGN:
		value = "Assign";
		break;
	case COMMAND_ENUM::DEVICE_CREATION:
		value = "Device Creation";
		break;
	case COMMAND_ENUM::INITALIZE_DEVICE:
		value = "Initalize Device";
		break;
	case COMMAND_ENUM::ON:
		value = "On";
		break;
	case COMMAND_ENUM::OFF:
		value = "Off";
		break;
	case COMMAND_ENUM::DEVICE_DESTRUCTION:
		value = "Device Destruction";
		break;
	case COMMAND_ENUM::NODE_CREATION:
		value = "Node Creation";
		break;
	case COMMAND_ENUM::NODE_INITALIZE:
		value = "Node Initalize";
		break;
	case COMMAND_ENUM::NODE_DESTORY:
		value = "Node Destroy";
		break;
	case COMMAND_ENUM::NODE_CONNECT:
		value = "Node Connect";
		break;
	case COMMAND_ENUM::NODE_DISCONNECT:
		value = "Node Disconnect";
		break;
	case COMMAND_ENUM::INVALID:
	default:
		value = "Invalid";
		break;
	}
	return value;
}