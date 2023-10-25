#include "../types/state.h"
#include "../Model/model_main.h"

void state_interfaces::mangle_state(Command* command)
{
	switch(command->get_id())
	{
	case COMMAND_ENUM::DEVICE_CREATION:
	{
		printf("Device Creation\n");
		Device_Create* device_create_command = static_cast<Device_Create*>(command);
		model::get_node(device_create_command->node)->register_device(device_create_command->device);
		break;
	}
	case COMMAND_ENUM::DEVICE_DESTRUCTION:
	{
		printf("Device Destruction\n");
		Device_Destruction* device_destruction_command = static_cast<Device_Destruction*>(command);
		model::get_node(device_destruction_command->get_device().get_node_id())->remove_device(device_destruction_command->get_device().get_device_id());
		break;
	}
	case COMMAND_ENUM::INITALIZE_DEVICE:
	{
		printf("Device Initalization\n");
		Initalize_Device* initalize_device_command = static_cast<Initalize_Device*>(command);
		model::get_device(initalize_device_command->get_label())->initalize(initalize_device_command->name);
		break;
	}
	case COMMAND_ENUM::ON:
	{
		printf("Device On\n");
		On* on_command = static_cast<On*>(command);
		model::get_device(on_command->get_label())->turn_on();
		break;
	}
	case COMMAND_ENUM::OFF:
	{
		printf("Device Off\n");
		Off* off_command = static_cast<Off*>(command);
		model::get_device(off_command->get_label())->turn_off();
		break;
	}
	case COMMAND_ENUM::ASSIGN:
	{
		printf("Device Assign\n");
		Assign* assign_command = static_cast<Assign*>(command);
		model::get_device(assign_command->get_label())->set_channel(assign_command->channel, assign_command->value);
		break;
	}
	case COMMAND_ENUM::NODE_CREATION:
	{
		printf("Node Creation\n");
		Node_Create* node_create_command = static_cast<Node_Create*>(command);
		model::create_node(node_create_command->get_type(), node_create_command->get_node_id());
		break;
	}
	case COMMAND_ENUM::NODE_DESTORY:
	{
		printf("Node Destroy\n");
		Node_Destroy* node_destroy_command = static_cast<Node_Destroy*>(command);
		model::remove_node(node_destroy_command->get_node_id());
		break;
	}
	case COMMAND_ENUM::NODE_INITALIZE:
	{
		printf("Node Initalize\n");
		Node_Initalize* node_initalize_command = static_cast<Node_Initalize*>(command);
		model::initalize_my_node(node_initalize_command->get_node_id());
		break;
	}
	case COMMAND_ENUM::NODE_CONNECT:
	{
		printf("Node Connect\n");
		Node_Connect* node_connect_command = static_cast<Node_Connect*>(command);
		model::connect_node(node_connect_command->get_connected_node(), node_connect_command->get_connecting_node_name());
		break;
	}
	case COMMAND_ENUM::NODE_DISCONNECT:
	{
		printf("Node Disconnect\n");
		Node_Disconnect* node_disconnect_command = static_cast<Node_Disconnect*>(command);
		model::disconnect_node(node_disconnect_command->get_disconnected_node(), node_disconnect_command->get_disconnecting_node());
		break;
	}
	case COMMAND_ENUM::INVALID:
	default:
		throw InvalidCommandException();
	}
}
