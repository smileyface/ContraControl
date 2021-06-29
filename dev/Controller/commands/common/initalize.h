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
	 * Device specific check for validity.
	 * \return If device is a valid device.
	 */
	virtual bool validity_check()
	{
		return true;
	}
};
#endif // !INITALIZE_COMMAND_H