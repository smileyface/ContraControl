/*****************************************************************//**
 * \file   state.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef STATE_INTERFACES_H
#define STATE_INTERFACES_H

#include "../Utilities/Utilities/exceptions.h"
#include "../Model/device.h"
#include "../Controller/commands.h"

/**
 * Device specific check for validity.
 * \return If device is a valid device.
 */
bool validity_check()
{
	return true;
}

/**
 Interfaces to handle device state
 */
namespace state_interfaces
{
	/**
	 Change state of device based on command.
	 \param command The Command that will mangle state.
	 \param state The state held in the Device.
	 */
	void mangle_state(Command* command, Device* state)
	{
		switch (command->get_id())
		{
		case COMMAND_ENUM::INVALID:
			throw InvalidCommandException();
		case COMMAND_ENUM::INITALIZE:
			state->initalize(static_cast<Initalize*>(command)->name);
			break;
		case COMMAND_ENUM::ON:
			state->turn_on();
			break;
		case COMMAND_ENUM::OFF:
			state->turn_off();
			break;
		case COMMAND_ENUM::TRANSITION:
		case COMMAND_ENUM::LINEAR_TRANSITION:
			command = static_cast<Transition*>(command);
			state->turn_on();
			//if not completed, you are transitioning
			static_cast<Channel_Device*>(state)->transitioning = !command->completed();

			if (state->get_device_type() >= DEVICE_IDENTIFIER::GRADIENT)
			{
				static_cast<Transition*>(command)->transition(*static_cast<Gradient_Device*>(state)->get_position_ptr());
			}

		}

	}
}
#endif
