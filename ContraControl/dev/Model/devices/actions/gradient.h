#ifndef GRADIENT_ACTION_INTERFACE_H
#define GRADIENT_ACTION_INTERFACE_H

#include "../gradient.h"
#include "device.h"

class Gradient_Action_Interface : protected Device_Action_Interface
{
public:
	void run_command(Command* command, Gradient& device)
	{
		Device_Action_Interface::run_command(command, device);
		switch (command->get_unique_id())
		{
		case COMMAND_ID::INITALIZE:
			device.set_position(0.0);
			break;
		case COMMAND_ID::ON:
			device.set_state(COMMAND_ID::ON);
			device.set_position(1.0f);
			break;
		case COMMAND_ID::OFF:
			device.set_state(COMMAND_ID::OFF);
			device.set_position(0.0);
			break;
		case COMMAND_ID::MOVE:
			device.set_state(COMMAND_ID::MOVE);
			device.set_position(dynamic_cast<Move*>(command)->amount);
			sys_log::log(LOG_PRIORITY::DEBUG, "Move to " + std::to_string(device.get_position() * 100), device.get_name());
		default:
			sys_log::log(LOG_PRIORITY::ERROR, "Invalid Gradient Command", device.get_name());
			break;
		}
	}
};

#endif // !GRADIENT_ACTION_INTERFACE_H