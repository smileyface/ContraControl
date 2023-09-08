/*****************************************************************//**
 * \file   packed_command.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/
#ifndef INTERFACE_PACKED_COMMAND_TYPE
#define INTERFACE_PACKED_COMMAND_TYPE

#include "Interfaces/types/device_label.h"
#include "../../../Controller/commands.h"

 /**
  Command with metadata attached for various uses
  */
class Packed_Command
{
public:
	Packed_Command();
	~Packed_Command();
	/**
	 @param cmd Command to run.
	 @param label Label that maps to the device to command.
	 @param time Time from start to run the command.
	 */
	Packed_Command(Command* cmd, double time);

	/**
	 Command to run
	 */
	Command* command;
	/**
	 Time to run.
	 */
	double time;
	/**
	 Has it been run?
	 */
	bool run;
	/**
	 * Has the command been sent to the model.
	 */
	bool sent;
};

/**
 List of Timed_Commands
 */
typedef std::vector<Packed_Command> Command_List;

#endif
