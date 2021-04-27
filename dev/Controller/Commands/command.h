/*****************************************************************//**
 * \file   command.h
 * \brief  
 * 
 * \author kason
 * \date   December 2020
 *********************************************************************/
#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "../../Model/state/state.h"

/*!
   An identifier object mainly for readability
 */
typedef uint16_t command_id;

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
	INVALID = UINT16_MAX
};

/*!
 *  An object to send the model a command that contains its own instructions for changing the state of a Device. Base class for all device commands. Made to code to this as an interface.
 */
class Command {
public:
	double time_to_complete = 0.0; ///<How long the command will take to run.
	Command() { };
	~Command() {};
    /**
     * \deprecated No longer implemented. Use mangle_state() instead. Will be removed in 0.0.5
     * \todo Remove this
     */
	virtual void step_command(double time_step) { } 
    /**
     * Change values in Device_State to reflect command.
     */
    virtual void mangle_state(Device_State& state) = 0;
    /**
     * If time to complete is 0, Command has completed, therefore return true.
     */
	bool completed() { return time_to_complete <= 0.0; }
    /**
     * Return Enum of the command. Mainly for Command indentification purposes.
     */
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INVALID; }
private:
};
/**
 * \todo Remove this
 */
inline std::string get_command_name(Command* command)
{
    switch (command->get_id())
    {
    case COMMAND_ENUM::INITALIZE:
        return "INITALIZE";
    case COMMAND_ENUM::TRANSITION:
        return "TRANSITION";
    case COMMAND_ENUM::LINEAR_TRANSITION:
        return "LINEAR_TRANSITION";
    case COMMAND_ENUM::ON:
        return "ON";
    case COMMAND_ENUM::OFF:
        return "OFF";
    case COMMAND_ENUM::INVALID:
    default:
        return "INVALID"; 
    }
    return "INVALID";
}

#endif // !COMMAND_H