#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class SwitchDevice: public Device
{
public:
	SwitchDevice(std::string name) {
		register_device(name);
	};
	~SwitchDevice() {};
	void run_command(Command* command) {
		Device::run_command(command);
		switch (command->get_unique_id())
		{
		case COMMAND_ID::INITALIZE:
			break;
		case COMMAND_ID::ON:
			state = COMMAND_ID::ON;
			break;
		case COMMAND_ID::OFF:
			state = COMMAND_ID::OFF;
			break;
		default:
			sys_log::log(LOG_PRIORITY::ERROR, "Invalid Swtich Command", name);
			break;
		}
	};
};

#endif // !SWITCH_DEVICE_H