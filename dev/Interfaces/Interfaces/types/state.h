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
#include "../Controller/commands.h"

/**
 Interfaces to handle device state
 */
namespace state_interfaces
{
	/**
	 Change state of device based on command.
	 \param command The Command that will mangle state.
	 */
	void mangle_state(Command* command);
}
#endif
