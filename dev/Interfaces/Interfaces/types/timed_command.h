/*****************************************************************//**
 * \file   timed_command.h
 * \brief  
 * 
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef INTERFACE_TIMED_COMMAND_TYPE
#define INTERFACE_TIMED_COMMAND_TYPE

#include "Interfaces/types/device_label.h"
#include "../../../Controller/commands.h"

/**
 Command with a timed element. 
 */
class Timed_Command {
public:
	/**
	 Command to run
	 */
	Command* command;
	/**
	 Label that maps to the device to command
	 */
	Device_Label device_label;
	/**
	 Time to run.
	 */
	double time;
	/**
	 Has it been run?
	 */
	bool run;

	/**
	 \param cmd Command to run.
	 \param label Label that maps to the device to command.
	 \param t Time from start to run the command.
	 */
	Timed_Command(Command* cmd, Device_Label label, double t) {
		command = cmd;
		device_label = label;
		time = t;
		run = false;
	};

	/**
	 \param tc Timed_Command to compare to.
	 \return If tc happens after this command.
	 */
	bool operator<(const Timed_Command& tc)
	{
		return time < tc.time;
	}

};

/**
 List of Timed_Commands
 */
typedef std::vector<Timed_Command> Timed_List;

#endif
