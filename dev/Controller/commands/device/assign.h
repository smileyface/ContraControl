/*****************************************************************//**
 * \file   assign.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/
#ifndef ASSIGN_COMMAND
#define ASSIGN_COMMAND

#include "device_command.h"
#include "Interfaces/types/channel.h"

 /**
  * A command to assign a channel a certain value.
  */
class Assign : public Device_Command {
public:

	Assign() = delete;
	/**
	 Set channel 0 to a specific value.
	 \param new_value Value to assign to channel 0
	 */
	Assign(Device_Label label, Channel new_value);
	/**
	 Set a channel to a specific value.
	 \param channel_number Designation of channel to assign value to.
	 \param new_value Value to assign to channel
	 */
	Assign(Device_Label label, int channel_number, Channel new_value);
	~Assign() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::ASSIGN; }

	/** Value to assign to designated channel */
	Channel value;
	/**  Channel to assign value to */
	int channel;
};

#endif // !ASSIGN_COMMAND