/*****************************************************************//**
 * \file   off.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/
#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "../command.h"

 /**
  * A command to turn devices off.
  */
class Off : public Command {
public:
 
	Off() {};
	~Off() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::OFF; }
    /**
    * Change values in Device_State to reflect command.<br>
    * If device is not initalized, set state to invalid and return.<br>
    * Set devices power state to off.
    * \param state reference to the state about to get mangled.
    */
    virtual void mangle_state(Device_State& state)
    {
        if(state.initalized == false)
        {
            state.valid = false;
            return;
        }
        state.power = false;
    }
};

#endif // !OFF_COMMAND
