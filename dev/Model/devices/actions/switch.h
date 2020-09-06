#ifndef SWITCH_ACTION_INTERFACE_H
#define SWTICH_ACTION_INTERFACE_H

#include "device.h"
#include "../basic/switch.h"

class Switch_Action_Interface : Device_Action_Interface
{
public:
	Switch_Action_Interface()
	{ 
	};
	~Switch_Action_Interface() {};
	void run_command(Command* command, Switch_Device& device) {
		Device_Action_Interface::run_command(command, device);
		switch (command->get_unique_id())
		{
		case COMMAND_ID::INITALIZE:
			break;
		case COMMAND_ID::ON:
			device.set_state(COMMAND_ID::ON);
			device.set_position(true);
			break;
		case COMMAND_ID::OFF:
			device.set_state(COMMAND_ID::OFF);
			device.set_position(false);
			break;
		default:
			sys_log::log(LOG_PRIORITY::ERROR, "Invalid Swtich Command", device.get_name());
			break;
		}
	};
protected:

};

#endif