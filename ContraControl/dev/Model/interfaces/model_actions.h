#ifndef MODEL_ACTION_INTERFACE_H
#define MODEL_ACTION_INTERFACE_H

#include <typeinfo>
#include <memory>
#include <iostream>

#include "../devices/actions/device.h"
#include "../devices/actions/gradient.h"
#include "../devices/actions/switch.h"

namespace model_action 
{
	void run_command(Command* command, Device& device)
	{
		if(typeid(device) == typeid(SwitchDevice))
		{
			Switch_Action_Interface sai;
			sai.run_command(command, static_cast<SwitchDevice&>(device));
		}
		else if (typeid(device) == typeid(Gradient))
		{
			Gradient_Action_Interface gai;
			gai.run_command(command, static_cast<Gradient&>(device));
		}
		else if (typeid(device) == typeid(Device))
		{

			std::cout << typeid(device).raw_name();
		}
	}
}

#endif // !MODEL_ACTION_INTERFACE_H

