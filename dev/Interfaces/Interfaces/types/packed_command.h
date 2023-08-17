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
	 @param t Time from start to run the command.
	 */
	Packed_Command(Command* cmd, Device_Label label, double t);
	/**.
	* @brief Instantaneous command. Will run on the next frame
	@param cmd Command to run.
	@param label Label that maps to the device to command.
	@param t Time from start to run the command.
	*/
	Packed_Command(Command* cmd, Device_Label label);
	/**
	 @param tc Timed_Command to compare to.
	 @return If tc happens after this command.
	 */
	bool operator<(const Packed_Command& tc);

	/**
	* Assignment operator.
	 * @param tc Timed_Command to copy to.
	 */
	void operator=(const Packed_Command& tc);
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
};

/**
 List of Timed_Commands
 */
typedef std::vector<Packed_Command> Command_List;

#endif
