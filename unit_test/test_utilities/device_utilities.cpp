#include "device_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
Node_Id device_utilities::node_handle = "Test_Node_1";
Device* device_utilities::get_nominal_state(DEVICE_IDENTIFIER device, Command* command)
{
	Device* ds = create_device_instance(Device_Creator((Device_Id)device, "Nominal"));

	ds->initalize("nominal");
	if (command->get_id() == COMMAND_ENUM::ON)
	{
		ds->turn_on();
	}
	return ds;
}

Device* device_utilities::get_nominal_state_no_init(DEVICE_IDENTIFIER device, Command* command)
{
	Device* ds = create_device_instance(Device_Creator((Device_Id)device, "Nominal"));

	if (command->get_id() == COMMAND_ENUM::ON)
	{
		ds->turn_on();
	}
	return ds;
}

void device_utilities::start_test_environment()
{
	system_util::setup();
	model::initalize_my_node(device_utilities::node_handle);
}

Device_Label device_utilities::add_device(Device_Creator creator)
{
	model::get_node(device_utilities::node_handle)->register_device(creator);
	return(Device_Label(device_utilities::node_handle, model::get_node(device_utilities::node_handle)->get_device(creator.second)->get_id()));
}

Device* device_utilities::command_device(Device_Label label, Command* command)
{
	controller::add_command(Timed_Command(command, label, 0));
	system_util::step(1);
	Device* ds = get_nominal_state(model::get_device(label)->get_device_type(), command);
	return ds;
}

Device* device_utilities::command_device_no_init(Device_Label label, Command* command)
{
	controller::add_command(Timed_Command(command, label, 0));
	system_util::step(1);
	return get_nominal_state_no_init(model::get_device(label)->get_device_type(), command);
}

Device* device_utilities::finish_command(Device_Label label, Command* command)
{
	while (!command->completed())
	{
		system_util::step(1);
	}
	system_util::step(1);
	return get_nominal_state(model::get_device(label)->get_device_type(), command);
}

void device_utilities::initalize_device(Device_Label label)
{
	command_device(label, new Initalize());
}