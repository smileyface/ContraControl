/*****************************************************************//**
 * \file   off.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/
#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "device_command.h"

 /**
  * A command to turn devices off.
  */
class Off : public Device_Command {
public:
 
	Off() = delete;
	/**
	 * \param label Label of the device to command.
	 */
	Off(Device_Label label);
	~Off();
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::OFF; }


};

#endif // !OFF_COMMAND
