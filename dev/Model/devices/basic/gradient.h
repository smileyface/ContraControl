#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "device.h"


class Gradient_Device: public Device
{
public:
	Gradient_Device() { position = 0.0; };
	~Gradient_Device() {};

	void set_position(float new_position)
	{
		position = new_position;
	};
	float get_position() 
	{
		return position;
	}

protected:
	void do_command(Command* command)
	{
		Device::do_command(command);
		switch (command->get_unique_id())
		{
		case COMMAND_ID::INITALIZE:
		case COMMAND_ID::OFF:
			set_position(0.0);
			break;
		case COMMAND_ID::ON:
			set_position(1.0f);
			break;
		case COMMAND_ID::TRANSITION:
			set_position(get_position() - dynamic_cast<Transition*>(command)->get_amount(model_timer.get_elapsed_time()));
			break;
		}
	};
private:
	float position;

};


#endif // !GRADIENT_DEVICE_H

