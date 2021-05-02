/*****************************************************************//**
 * \file   initalize.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include "../command.h"

class Initalize : public Command
{
public:
	~Initalize() {};
	std::string name;
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INITALIZE; }
	/**
	* Change values in Device_State to reflect command.<br>
	* Sets initalized as true. This should be set to run a function on a per device basis. <br>
	* sets validity to true.<br>
	* Sets position to neutral. (defaults to 0)
	*/
    virtual void mangle_state(Device_State& state)
    {
        state.initalized = true;
        state.valid = validity_check();
		state.position = 0.0f;
    }

	virtual bool validity_check()
	{
		return true;
	}
};
#endif // !INITALIZE_COMMAND_H