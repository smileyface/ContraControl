/*****************************************************************//**
 * \file   packed_command.h
 * \brief  
 * 
 * \author kason
 * \date   August 2023
 *********************************************************************/
#ifndef INTERFACE_PACKED_COMMAND_TYPE
#define INTERFACE_PACKED_COMMAND_TYPE

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
	 * Copy constructor.
	 * 
	 * @param cmd Packed_Command to copy
	 */
	Packed_Command(const Packed_Command& cmd);
	/**
	 @param cmd Command to run.
	 @param time Time from start to run the command.
	 */
	Packed_Command(Command* cmd, double time);

	/**
	 * Move time forward
	 * \param elapse_time Amount to decrement the time delay by.
	 */
	void move_time(double elapse_time);

	/**
	 * \return Time offset.
	 */
	double get_time() const;
	/**
	 * \return Pointer to the command.
	 */
	Command* get_command() const;

	/**
	 * \return If the message has been sent from the Controller to the Model.
	 */
	bool command_sent() const;
	/**
	 * \return If the command has been run from the Model.
	 */
	bool command_run() const;

	/**
	 * Set the send flag
	 */
	void send_command();
	/**
	 * Set the run flag
	 */
	void run_command();

	/**
	* \param rhs Right hand object
	* \return true if the command on the right hand is at the same pointer location as this.
	*/
	bool operator==(const Packed_Command& rhs) const; 

private:
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
