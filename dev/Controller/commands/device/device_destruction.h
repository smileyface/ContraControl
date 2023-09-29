/*****************************************************************//**
 * \file   device_destruction.h
 * \brief  
 * 
 * \author kason
 * \date   September 2023
 *********************************************************************/

#ifndef DEVICE_DESTRUCTION_COMMAND_H
#define DEVICE_DESTRUCTION_COMMAND_H

#include "../command.h"
#include "Interfaces/types/device_label.h"

class Device_Destruction : public Command
{
public:
	Device_Destruction() = delete;
	~Device_Destruction();

	Device_Destruction(Device_Label label);

	Device_Label get_device();

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::DEVICE_DESTRUCTION;
	}
private:
	/**
 * ID of the device and the common name to be created on the node.
 */
	Device_Label device;
};

#endif // !DEVICE_DESTRUCTION_COMMAND_H
