/*****************************************************************//**
 * \file   device_command.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/
#ifndef DEVICE_COMMAND_BASE
#define DEVICE_COMMAND_BASE
#include "../command.h"
#include "Interfaces/enums/device_type.h"

/**
 * Base class for commanding devices.
 */
class Device_Command : public Command
{
public:
	Device_Command()
	{ }
	virtual ~Device_Command()
	{ }
	/**
	 * Identifier of device to command
	 * 
	 * \param label Label for the device.
	 */
	virtual void set_label(Device_Label label);
	/**
	 * \return label of the device to command.
	 */
	virtual Device_Label get_label();
protected:
	/** Device to command */
	Device_Label label;
};

#endif