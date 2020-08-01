#include "device.h"


void Device::run_command(Command command)
{
	switch (command.unique_id)
	{
	case COMMAND_ID::INITALIZE:
		break;
	case COMMAND_ID::OFF:
		break;
	case COMMAND_ID::ON:
		break;
	default:
		break;
	}
}

