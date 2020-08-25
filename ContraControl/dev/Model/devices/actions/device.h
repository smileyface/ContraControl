#ifndef DEVICE_INTERFACE_H
#define DEVICE_INTERFACE_H
#include "../../../Utilities/Logging/logging.h"
#include "../device.h"

static uint16_t device_id_pool = 0;

class Device_Action_Interface {
public:
	Device_Action_Interface() { };
	virtual void run_command(Command* command, Device& dev ) {
		switch (command->get_unique_id())
		{
		case COMMAND_ID::INITALIZE:
			dev.set_state(COMMAND_ID::INITALIZE);
			dev.set_id(device_id_pool);
			device_id_pool++;
			dev.set_name(static_cast<Initalize*>(command)->name);
			sys_log::log(LOG_PRIORITY::DEBUG, "Initalizing", dev.get_name());
			break;
		case COMMAND_ID::OFF:
			sys_log::log(LOG_PRIORITY::DEBUG, "Off", dev.get_name());
			break;
		case COMMAND_ID::ON:
			sys_log::log(LOG_PRIORITY::DEBUG, "On", dev.get_name());
			break;
		case COMMAND_ID::MOVE:
			sys_log::log(LOG_PRIORITY::DEBUG, "Movement", dev.get_name());
			break;
		default:
			dev.set_state(COMMAND_ID::INVALID);
			sys_log::log(LOG_PRIORITY::ERROR, "Invalid Device Command", dev.get_name());
			break;
		}
	};

protected:
};

#endif