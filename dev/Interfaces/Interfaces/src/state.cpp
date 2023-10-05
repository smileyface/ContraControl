#include "../types/state.h"
#include "../Model/model_main.h"

void state_interfaces::mangle_state(Command* command)
{
	switch(command->get_id())
	{
	case COMMAND_ENUM::DEVICE_CREATION:
	{
		Device_Create* device_create_command = static_cast<Device_Create*>(command);
		model::get_node(device_create_command->node)->register_device(device_create_command->device);
		break;
	}
	case COMMAND_ENUM::DEVICE_DESTRUCTION:
	{
		Device_Destruction* device_destruction_command = static_cast<Device_Destruction*>(command);
		model::get_node(device_destruction_command->get_device().get_node_id())->remove_device(device_destruction_command->get_device().get_device_id());
		break;
	}
	case COMMAND_ENUM::INITALIZE_DEVICE:
	{
		Initalize_Device* initalize_device_command = static_cast<Initalize_Device*>(command);
		model::get_device(initalize_device_command->get_label())->initalize(initalize_device_command->name);
		break;
	}
	case COMMAND_ENUM::ON:
	{
		On* on_command = static_cast<On*>(command);
		model::get_device(on_command->get_label())->turn_on();
		break;
	}
	case COMMAND_ENUM::OFF:
	{
		Off* off_command = static_cast<Off*>(command);
		model::get_device(off_command->get_label())->turn_off();
		break;
	}
	case COMMAND_ENUM::ASSIGN:
	{
		Assign* assign_command = static_cast<Assign*>(command);
		model::get_device(assign_command->get_label())->set_channel(assign_command->channel, assign_command->value);
		break;
	}
	case COMMAND_ENUM::NODE_CREATION:
	{
		Node_Create* node_create_command = static_cast<Node_Create*>(command);
		model::create_node(node_create_command->get_type(), node_create_command->get_node_id());
		break;
	}
	case COMMAND_ENUM::NODE_DESTORY:
	{
		Node_Destroy* node_destroy_command = static_cast<Node_Destroy*>(command);
		model::remove_node(node_destroy_command->get_node_id());
		break;
	}
	case COMMAND_ENUM::INVALID:
	default:
		throw InvalidCommandException();
	}
}
