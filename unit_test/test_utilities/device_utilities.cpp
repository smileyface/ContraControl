#include <utility>
#include <iostream>

#include "device_utilities.h"
#include "system_utilities.h"
#include "module_mains.h"

int device_utilities::device_in_use = 0;
Node_Id device_utilities::node_handle = "Test_Node_1";
std::map<Device_Id, Device*> device_utilities::model_list;
std::vector<Packed_Command> command_list;

Device* device_utilities::get_nominal_state(Device_Id label, Command* command)
{
	if(model_list[label] == nullptr)
	{
		LOG_ERROR("Device not in testing model", "Testing Device Utilities");
	}
	else if (command->get_id() == COMMAND_ENUM::INITALIZE_DEVICE)
	{
		model_list[label]->initalize("nominal");
	}
	else if (command->get_id() == COMMAND_ENUM::ON)
	{
		model_list[label]->turn_on();
	}
	else if (command->get_id() == COMMAND_ENUM::OFF)
	{
		model_list[label]->turn_off();
	}
	return model_list[label];
}

void device_utilities::start_test_environment()
{
	printf("Test Adding Node\n");
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Create>(NODE_TYPE::TEST, device_utilities::node_handle), 0));
	printf("Test Initalizing Node\n");
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Node_Initalize>(device_utilities::node_handle), 0));
	system_utilities::run_all_queued_commands();
}



Device_Label device_utilities::add_device(Device_Creator creator)
{
	printf("Test Adding Device\n");
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Device_Create>(device_utilities::node_handle, creator.first, creator.second), 0));
	system_utilities::run_all_queued_commands();
	Node* my_node = model::get_node(device_utilities::node_handle);
	Device* my_device = my_node->get_device(creator.second);
	if(my_device == nullptr)
	{
		printf("Test Device not created\n");
		return Device_Label(device_utilities::node_handle, -1);
	}

	model_list[model::get_node(device_utilities::node_handle)->get_device(creator.second)->get_id()] = create_device_instance(creator);
	return(Device_Label(device_utilities::node_handle, model::get_node(device_utilities::node_handle)->get_device(creator.second)->get_id()));
}

void device_utilities::remove_device(Device_Label label)
{
	controller::add_command(Packed_Command(Commander::get_instance()->make_command<Device_Destruction>(label), 0));
	system_utilities::run_all_queued_commands();
}

Device* device_utilities::command_device(Device_Label label, Command* command)
{
	return command_device(label, command, 0);
}

Device* device_utilities::command_device(Device_Label label, Command* command, double delay)
{
	std::cout << "Test commanding device " << label.get_node_id() << ":" << label.get_device_id() << " - " << static_cast<int>(command->get_id()) << std::endl;
	Device_Command* d_command = static_cast<Device_Command*>(command);
	controller::add_command(Packed_Command(command, delay));
	system_utilities::run_all_queued_commands();
	return model_list[label.get_device_id()];
}

void device_utilities::add_command(Command* command)
{
	controller::add_command(Packed_Command(command, 0));
}

Device* device_utilities::finish_command(Device_Label label, Command* command)
{
	while (!command->completed())
	{
		system_utilities::step(1);
	}
	system_utilities::step(1);
	return get_nominal_state(label.get_device_id(), command);
}