#include "device.h"


void Device::run_command(Command* command)
{
	switch (command->get_unique_id())
	{
	case COMMAND_ID::INITALIZE:
		state = COMMAND_ID::INITALIZE;
		_log.logging.emplace_back(LogItem(LOG_PRIORITY::DEBUG, "Initalizing", name));
		break;
	case COMMAND_ID::OFF:
		_log.logging.emplace_back(LogItem(LOG_PRIORITY::DEBUG, "Off", name));
		break;
	case COMMAND_ID::ON:
		_log.logging.emplace_back(LogItem(LOG_PRIORITY::DEBUG, "On", name));
		break;
	default:
		_log.logging.emplace_back(LogItem(LOG_PRIORITY::ERROR, "Invalid Device Command", name));
		break;
	}
}

