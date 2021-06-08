/*****************************************************************//**
 * \file   on.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef ON_COMMAND_H
#define ON_COMMAND_H


#include "../command.h"

/**
 * A command to turn devices on.
 */
class On : public Command {
public:
	On() {};
	~On() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::ON; }
    /**
     * Change values in Device_State to reflect command.<br>
     * If device is not initalized, set state to invalid and return.<br>
     * Set devices power state to on.
     * \param state reference to the state about to get mangled.
     */
    virtual void mangle_state(Device_State& state)
    {
        if(state.initalized == false)
        {
            state.valid = false;
            return;
        }
        state.power = true;
    }
};
#endif // !ON_COMMAND_H
