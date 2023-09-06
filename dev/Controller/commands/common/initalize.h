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
#include "Interfaces/types/device_label.h"

/**
 * Run device initalization. Name device and check for validity.
 */
class Initalize : public Command
{
public:
	~Initalize() {};
	/**
	 * Construct command with the name to give to the device.
	 * \param device_common_name Common name of device.
	 */
	Initalize(std::string device_common_name);
	/**
	 Name for the device to be initalized
	 */
	std::string name;
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INITALIZE; }
	/** Device to command */
	Device_Label label;

};
#endif // !INITALIZE_COMMAND_H