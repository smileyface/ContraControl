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

class Command {
public:
	double time_to_complete = 0.0;
	Command() { };
	~Command() {};
	virtual void step_command(double time_step) { }
    virtual void mangle_state(Device_State& state) = 0;
	bool completed() { return time_to_complete <= 0.0; }
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INVALID; }
private:
};

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