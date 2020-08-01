#include "device.h"


Device::Device()
{
}


void Device::run_command(Command command)
{
	switch (command.unique_id)
	{
	case COMMAND_ID::INITALIZE:
		break;
	default:
		break;
	}
}

