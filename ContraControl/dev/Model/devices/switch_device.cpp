#include "switch_device.h"

SwitchDevice::SwitchDevice()
{
	SwitchDevice::add_command(SWITCH_DEVICE_COMMANDS::INITALIZE, Command_Func{
		state = SWITCH_DEVICE_COMMANDS::INITALIZE;
	});
	SwitchDevice::add_command(SWITCH_DEVICE_COMMANDS::ON, Command_Func{
		state = SWITCH_DEVICE_COMMANDS::ON;
	});
	SwitchDevice::add_command(SWITCH_DEVICE_COMMANDS::OFF, Command_Func{
		state = SWITCH_DEVICE_COMMANDS::OFF;
	});
}

void SwitchDevice::initalize() {
	Device::initalize();
}
