/*****************************************************************//**
 * \file   initalize.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include <string>			//std::string

#include "../command.h"

/**
 * Run device initalization. Name device and check for validity.
 */
class Initalize : public Command
{
public:
	~Initalize() {};
	/**
	 Name for the device to be initalized
	 */
	std::string name;
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INITALIZE; }
	/**
	* Change values in Device_State to reflect command.<br>
	* Sets initalized as true. This should be set to run a function on a per device basis. <br>
	* sets validity to true.<br>
	* Sets position to neutral. (defaults to 0)
	* \param state reference to the state about to get mangled.
	*/
    virtual void mangle_state(Device_State& state)
    {
        state.initalized = true;
        state.valid = validity_check();
    }

	/**
	 * Device specific check for validity.
	 * \return If device is a valid device.
	 */
	virtual bool validity_check()
	{
		return true;
	}
};
#endif // !INITALIZE_COMMAND_H