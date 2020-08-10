#include <string>

#include "device.h"


void Device::run_command(Command* command)
{
	switch (command->get_unique_id())
	{
	case COMMAND_ID::INITALIZE:
		state = COMMAND_ID::INITALIZE;
		sys_log::log(LOG_PRIORITY::DEBUG, "Initalizing", name);
		break;
	case COMMAND_ID::OFF:
		sys_log::log(LOG_PRIORITY::DEBUG, "Off", name);
		break;
	case COMMAND_ID::ON:
		sys_log::log(LOG_PRIORITY::DEBUG, "On", name);
		break;
	case COMMAND_ID::MOVE:
		sys_log::log(LOG_PRIORITY::DEBUG, "Movement", name);
	default:
		sys_log::log(LOG_PRIORITY::ERROR, "Invalid Device Command", name);
		break;
	}
}

