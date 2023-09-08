/*****************************************************************//**
 * \file   device_initalize.h
 * \brief  
 * 
 * \author kason
 * \date   September 2023
 *********************************************************************/
#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include <string>			//std::string

#include "device_command.h"
#include "Interfaces/types/device_label.h"

 /**
  * Run device initalization. Name device and check for validity.
  */
class Initalize_Device : public Device_Command
{
public:
	Initalize_Device() = delete;
	~Initalize_Device();
	/**
	 * Construct command for a device.
	 * \param device_common_name Common name of device.
	 */
	Initalize_Device(Device_Label label, std::string device_common_name);

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::INITALIZE;
	}
	/**
 Name for the device to be initalized
 */
	std::string name;

};
#endif // !INITALIZE_COMMAND_H