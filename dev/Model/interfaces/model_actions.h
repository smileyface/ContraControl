#ifndef MODEL_ACTION_INTERFACE_H
#define MODEL_ACTION_INTERFACE_H

#include <typeinfo>
#include <memory>
#include <iostream>

#include "../devices/actions/device.h"
#include "../devices/actions/gradient.h"
#include "../devices/actions/switch.h"
#include "../../Utilities/Logging/logging.h"

namespace model_action 
{
	void run_command(Command* command, Device& device)
	{
		if(typeid(device) == typeid(Switch_Device))
		{
			Switch_Action_Interface sai;
			sai.run_command(command, static_cast<Switch_Device&>(device));
		}
		else if (typeid(device) == typeid(Gradient_Device))
		{
			Gradient_Action_Interface gai;
			gai.run_command(command, static_cast<Gradient_Device&>(device));
		}
		else if (typeid(device) == typeid(Device))
		{
			Device_Action_Interface dai;
			dai.run_command(command, static_cast<Device&>(device));
		}
		else
		{
			Logger::getInstance()->addItem(LOG_PRIORITY::ERROR, "Command Sent to Invalid Device", device.get_name());
		}
	}
}

#endif // !MODEL_ACTION_INTERFACE_H

