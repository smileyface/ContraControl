#ifndef SWITCH_DEVICE_H
#define SWITCH_DEVICE_H

#include "device.h"

class Switch_Device: public Device
{
public:
	Switch_Device() { position = false; };
	~Switch_Device() {};

	void set_position(bool new_position)
	{
		position = new_position;
	}

	bool get_position()
	{
		return position;
	}

protected:
	virtual void do_command(Command* command)
	{
		Device::do_command(command);
		switch (command->get_unique_id())
		{
		case(COMMAND_ID::INITALIZE):
		case(COMMAND_ID::OFF):
			set_position(false);
			break;
		case(COMMAND_ID::ON):
			set_position(true);
			break;
		}
	};

private:
	bool position;

};

#endif // !SWITCH_DEVICE_H