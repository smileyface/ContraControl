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
		}
		state->notify_view();
	}
}
#endif
