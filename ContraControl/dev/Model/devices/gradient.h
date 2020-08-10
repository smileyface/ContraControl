#ifndef GRADIENT_DEVICE_H
#define GRADIENT_DEVICE_H

#include "device.h"

class Gradient: public Device
{
public:
	Gradient() {};
	~Gradient() {};
	void run_command(Command* command)
	{
		Device::run_command(command);
		switch (command->get_unique_id())
		{
		case COMMAND_ID::INITALIZE:
			position = 0.0;
			break;
		case COMMAND_ID::ON:
			state = COMMAND_ID::ON;
			position = 1.0;
			break;
		case COMMAND_ID::OFF:
			state = COMMAND_ID::OFF;
			position = 0.0;
			break;
		case COMMAND_ID::MOVE:
			state = COMMAND_ID::MOVE;
			position = dynamic_cast<Move*>(command)->amount;
		default:
			_log.logging.push_back(LogItem(LOG_PRIORITY::ERROR, "Invalid Gradient Command", name));
			break;
		}
	};

private:
	float position;

};


#endif // !GRADIENT_DEVICE_H

