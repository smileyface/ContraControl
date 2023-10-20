/*****************************************************************//**
 * \file   device_destruction.h
 * \brief  
 * 
 * \author kason
 * \date   September 2023
 *********************************************************************/

#ifndef DEVICE_DESTRUCTION_COMMAND_H
#define DEVICE_DESTRUCTION_COMMAND_H

#include "device_command.h"

 /**
  * A command for the Model to remove a device from a designated Node.
  */
class Device_Destruction : public Device_Command
{
public:
	Device_Destruction() = delete;
	~Device_Destruction();

	/**
	 * Constructor
	 * \param label The label for the Device to remove of from the node.
	 */
	Device_Destruction(Device_Label label);

	/**
	 * \return Label for the device to remove.
	 */
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
