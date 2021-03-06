#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class Switch_Device: public Device
{
public:
	Switch_Device() { };
	~Switch_Device() {};

	bool get_power()
	{
		return state.power;
	}
	virtual void do_command(Command* command)
	{
		Device::do_command(command);
		switch (command->get_id())
		{
		case COMMAND_ENUM::INITALIZE:
		case COMMAND_ENUM::OFF:
			state.power = false;
			break;
		case COMMAND_ENUM::ON:
			state.power = true;
			break;
		default:
			state.valid = false;
		}
	};

private:

};

#endif // !SWITCH_DEVICE_H