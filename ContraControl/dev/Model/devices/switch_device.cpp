#include "switch_device.h"

SwitchDevice::SwitchDevice()
{

}

void SwitchDevice::run_command(Command command)
{
	switch (command.unique_id)
	{
	case COMMAND_ID::INITALIZE:
		Device::run_command(command);
	default:
		break;
	}
}