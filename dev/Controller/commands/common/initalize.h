/*****************************************************************//**
 * \file   initalize.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef INITALIZE_GENERAL_H
#define INITALIZE_GENERAL_H

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
	 * Construct command for a device.
	 * \param device_common_name Common name of device.
	 */
	Initalize(std::string device_common_name);

	virtual COMMAND_ENUM get_id()
	{
		return COMMAND_ENUM::INITALIZE_DEVICE;
	}
	/**
 Name for the device to be initalized
 */
	std::string name;

};
#endif // !INITALIZE_COMMAND_H