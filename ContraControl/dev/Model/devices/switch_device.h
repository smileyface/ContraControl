#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class SwitchDevice: public Device
{
public:
	SwitchDevice() { register_device(); };
	~SwitchDevice() {};
	void run_command(Command command)
	{
		Device::run_command(command);
		switch (command.unique_id)
		{
		case COMMAND_ID::INITALIZE:
			break;
		case COMMAND_ID::ON:
			state = COMMAND_ID::ON;
		case COMMAND_ID::OFF:
			state = COMMAND_ID::OFF;
		default:
			break;
		}
	};
};

#endif // !SWITCH_DEVICE_H