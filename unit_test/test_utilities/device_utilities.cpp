#include "device_utilities.h"
#include "system_testings.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
Node_Id device_utilities::node_handle = "Test_Node_1";
std::map<Device_Id, Device*> device_utilities::model_list;

Device* device_utilities::get_nominal_state(Device_Id label, Command* command)
{
	if (command->get_id() == COMMAND_ENUM::INITALIZE)
	{
		model_list[label]->initalize("nominal");
	}
	if (command->get_id() == COMMAND_ENUM::ON)
	{
		model_list[label]->turn_on();
	}
	if (command->get_id() == COMMAND_ENUM::OFF)
	{
		model_list[label]->turn_off();
	}
	return model_list[label];
}

void device_utilities::start_test_environment()
{
	system_util::setup();
	model::initalize_my_node(device_utilities::node_handle);
}

Device_Label device_utilities::add_device(Device_Creator creator)
{
	model::get_node(device_utilities::node_handle)->register_device(creator);
	model_list[model::get_node(device_utilities::node_handle)->get_device(creator.second)->get_id()] = create_device_instance(creator);
	return(Device_Label(device_utilities::node_handle, model::get_node(device_utilities::node_handle)->get_device(creator.second)->get_id()));
}

void device_utilities::remove_device(Device_Label label)
{
	model::get_node(label.get_node_id())->remove_device(label.get_device_id());
}

Device* device_utilities::command_device(Device_Label label, Command* command)
{
	controller::add_command(Timed_Command(command, label, 0));
	system_util::step(1);
	Device* ds = get_nominal_state(label.get_device_id(), command);
	return ds;
}

void device_utilities::add_command(Device_Label label, Command* command)
{
	controller::add_command(Timed_Command(command, label, 0));
	controller::step();
}

Device* device_utilities::finish_command(Device_Label label, Command* command)
{
	while (!command->completed())
	{
		system_util::step(1);
	}
	system_util::step(1);
	return get_nominal_state(label.get_device_id(), command);
}