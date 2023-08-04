/*****************************************************************//**
 * \file   command.h
 * \brief  
 * 
 * \author kason
 * \date   December 2020
 *********************************************************************/
#ifndef COMMAND_H
#define COMMAND_H

/*!
   An identifier object mainly for readability
 */
typedef unsigned short command_id;

/*!
   An enumerated list of command types
 */
enum class COMMAND_ENUM :command_id
{
    /**
     Do device start up routine
     */
	INITALIZE,
    /**
     Turn device on
     */
	ON,
    /**
     Turn device off
     */
	OFF,
    /**
     Assign value to a channel
     */
     ASSIGN,
    /**
     Generic transition
     */
	TRANSITION,
    /**
     Transition at in a linear manner
     */
	LINEAR_TRANSITION,
    /**
     Unmapped Command
     */
	INVALID = 0xffff
};

/*!
 *  An object to send the model a command that contains its own instructions for changing the state of a Device. Base class for all device commands. Made to code to this as an interface.
 */
class Command {
public:
    /**
     How long the command will take to run.
     */
	double time_to_complete = 0.0;
	Command();

    /**
     * \return If time to complete is 0, Command has completed, therefore return true.
     */
    virtual bool completed();

    /**
     * @brief Set if a command has been completed by the Subsystem that the command was sent to.
     */
    void complete_command();
    /**
     * Return Enum of the command. Mainly for Command indentification purposes.
     * \return Enum value of the command.
     */
    virtual COMMAND_ENUM get_id();
private:
    bool complete;
};


#endif // !COMMAND_H
