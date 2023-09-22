#include "../types/state.h"
#include "../Model/model_main.h"

void state_interfaces::mangle_state(Command* command)
{
	switch(command->get_id())
	{
	case COMMAND_ENUM::DEVICE_CREATION:
		model::get_node(static_cast<Device_Create*>(command)->node)->register_device(static_cast<Device_Create*>(command)->device);
		break;
	case COMMAND_ENUM::INITALIZE:
		model::get_device(static_cast<Initalize_Device*>(command)->get_label())->initalize(static_cast<Initalize_Device*>(command)->name);
		break;
	case COMMAND_ENUM::ON:
		model::get_device(static_cast<On*>(command)->get_label())->turn_on();
		break;
	case COMMAND_ENUM::OFF:
		model::get_device(static_cast<Off*>(command)->get_label())->turn_off();
		break;
	case COMMAND_ENUM::ASSIGN:
		model::get_device(static_cast<Assign*>(command)->get_label())->set_channel(static_cast<Assign*>(command)->channel, static_cast<Assign*>(command)->value);
		break;
	case COMMAND_ENUM::INVALID:
	default:
		throw InvalidCommandException();
	}
}
