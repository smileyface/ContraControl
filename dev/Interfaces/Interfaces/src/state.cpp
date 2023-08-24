#include "../types/state.h"
#include "../Model/model_main.h"

void state_interfaces::mangle_state(Command* command, Device* state)
{
	if(state->get_device_type() > DEVICE_IDENTIFIER::INVALID)
	{
		throw InvalidDeviceException();
	}
	switch(command->get_id())
	{
	case COMMAND_ENUM::DEVICE_CREATION:
		model::get_node(static_cast<Device_Create*>(command)->node)->register_device(static_cast<Device_Create*>(command)->device);
		break;
	case COMMAND_ENUM::INITALIZE:
		state->initalize(static_cast<Initalize*>(command)->name);
		break;
	case COMMAND_ENUM::ON:
		state->turn_on();
		break;
	case COMMAND_ENUM::OFF:
		state->turn_off();
		break;
	case COMMAND_ENUM::ASSIGN:
		state->set_channel(static_cast<Assign*>(command)->channel, static_cast<Assign*>(command)->value);
		break;
	case COMMAND_ENUM::DEVICE_DESTRUCTION:
		break;
	case COMMAND_ENUM::INVALID:
		throw InvalidCommandException();
	}
}
