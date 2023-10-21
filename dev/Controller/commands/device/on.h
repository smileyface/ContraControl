/*****************************************************************//**
 * \file   on.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef ON_COMMAND_H
#define ON_COMMAND_H


#include "device_command.h"

/**
 * A command to turn devices on.
 */
class On : public Device_Command {
public:
	On() = delete;
	/**
	 * \param label Label of the device to command.
	 */
	On(Device_Label label);
	~On();
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::ON; }
};
#endif // !ON_COMMAND_H
