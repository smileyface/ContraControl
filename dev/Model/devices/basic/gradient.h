#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "device.h"


class Gradient_Device: public Device
{
public:
	Gradient_Device() {};
	~Gradient_Device() {};

	float get_position() 
	{
		return state.position;
	}

	virtual void do_command(Command* command)
	{
		Device::do_command(command);
		switch (command->get_id())
		{
		case COMMAND_ENUM::INITALIZE:
		case COMMAND_ENUM::OFF:
			state.power = false;
			state.position = 0.0;
			break;
		case COMMAND_ENUM::ON:
			state.power = true;
			state.position = 1.0;
			break;
		case COMMAND_ENUM::TRANSITION:
			state.power = true;
			state.transitioning = true;
			dynamic_cast<Transition*>(command)->transition(state.position, model_timer.get_elapsed_time());
			if (command->completed())
			{
				state.transitioning = false;
			}
			break;
		default:
			state.valid = false;
		}
	};

private:

};


#endif // !GRADIENT_DEVICE_H

