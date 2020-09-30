#include "device_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
device_state device_utilities::get_nominal_state(Command* command)
{
		device_state ds;
		switch (command->get_id())
		{
		case COMMAND_ENUM::TRANSITION:
			ds.transitioning = true;
		case COMMAND_ENUM::ON:
			ds.power = true;
		case COMMAND_ENUM::OFF:
		case COMMAND_ENUM::INITALIZE:
			ds.initalized = true;
			ds.valid = true;
			break;
		}
		return ds;
}
std::string device_utilities::add_device(Device* dev)
{
	device_in_use++;
	model::add_device(std::to_string(device_in_use), dev);
	system_util::setup();
	system_util::step(1);
	return(std::to_string(device_in_use));
}

device_state device_utilities::command_device(std::string device_id, Command* command)
{
	controller::add_command(Timed_Command(command, model::get_device(device_id)->get_id(), 0));
	system_util::step(1);
	return get_nominal_state(command);
}

device_state device_utilities::finish_command(Command* command)
{
	while (!command->completed())
	{
		system_util::step(1);
	}
	return get_nominal_state(command);
}

void device_utilities::check_state(std::string device, device_state expected_state)
{
	device_state received_state;
	received_state.switches_unpack(model::get_device(device)->get_state_switches());

	EXPECT_EQ(received_state.initalized, expected_state.initalized) << "Device is not initalized properly";
	EXPECT_EQ(received_state.power, expected_state.power) << "Device power is not correct";
	EXPECT_EQ(received_state.transitioning, expected_state.transitioning) << "Device transition is not correct";
	EXPECT_EQ(received_state.valid, expected_state.valid) << "Device validity is not correct";
}

void device_utilities::check_position(std::string device, float position)
{
	EXPECT_EQ(model::get_device(device)->get_position(), position/100);
}
