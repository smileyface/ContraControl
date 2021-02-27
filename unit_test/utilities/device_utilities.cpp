#include "device_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
Device_State device_utilities::get_nominal_state(Command* command)
{
		Device_State ds;
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

void device_utilities::create_node(Node_Id id)
{
	model::create_node(Node_Type::TEST, id);
}

Device_Label device_utilities::add_device(Node_Id id, Device* dev)
{
	device_in_use++;
	dev->set_id(device_in_use);
	model::get_node(id)->register_device(dev);
	system_util::setup();
	system_util::step(1);
	return(Device_Label(id, device_in_use));
}

Device_State device_utilities::command_device(Device_Label label, Command* command)
{
	//controller::add_command(Timed_Command(command, model
	//	::get_node("node1").get_device(device_id)->get_id(), 0));
	system_util::step(1);
	return get_nominal_state(command);
}

Device_State device_utilities::finish_command(Command* command)
{
	while (!command->completed())
	{
		system_util::step(1);
	}
	return get_nominal_state(command);
}

void device_utilities::check_state(Device_Label device, Device_State expected_state)
{
	Device_State received_state;
	received_state.switches_unpack(model::get_device(device)->get_state_switches());


	EXPECT_EQ(received_state.valid, expected_state.valid) << "Device validity is not correct";
	EXPECT_EQ(received_state.initalized, expected_state.initalized) << "Device is not initalized properly";
	EXPECT_EQ(received_state.power, expected_state.power) << "Device power is not correct";
	EXPECT_EQ(received_state.transitioning, expected_state.transitioning) << "Device transition is not correct";
}

void device_utilities::check_position(std::string device, float position)
{
	//EXPECT_EQ(model::get_node("node1").get_device(device)->get_position(), position/100);
}

void device_utilities::check_validity(std::string device, bool expect_valid)
{
	Device_State received_state;
	//received_state.switches_unpack(model::get_node("node1").get_device(device)->get_state_switches());

	EXPECT_EQ(received_state.valid, expect_valid) << "Device validity is not correct";
}

void device_utilities::initalize_device(Device_Label label)
{
	command_device(label, new Initalize(std::to_string(label.second)));
}