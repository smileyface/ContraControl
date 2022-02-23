/*****************************************************************//**
 * \file   assign.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/
#ifndef ASSIGN_COMMAND
#define ASSIGN_COMMAND

#include "../command.h"
#include "Interfaces/types/channel.h"

 /**
  * A command to assign a channel a certain value.
  */
class Assign : public Command {
public:

	Assign() 
	{
		channel = 0;
		value = 0;
	};
	/**
	 Set channel 0 to a specific value.
	 */
	Assign(Channel new_value);
	/**
	 Set a channel to a specific value.
	 */
	Assign(int channel_number, Channel new_value);
	~Assign() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::ASSIGN; }

	Channel value;
	int channel;
};

#endif // !ASSIGN_COMMAND