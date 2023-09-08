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

class Device_Command : public Command
{
public:
	Device_Command()
	{ }
	virtual ~Device_Command()
	{ }

	virtual void set_label(Device_Label label);
	virtual Device_Label get_label();
protected:
	/** Device to command */
	Device_Label label;
};

#endif