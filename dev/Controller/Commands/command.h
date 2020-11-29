#ifndef COMMAND_H
#define COMMAND_H

#include <utility>

#include <cinttypes>
#include <string>
#include <typeinfo>

#include "../../Model/state/state.h"

typedef uint16_t command_id;

enum class COMMAND_ENUM :uint16_t
{
	INITALIZE,
	ON,
	OFF,
	TRANSITION,
	LINEAR_TRANSITION,
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
        return "INVALID"; 
    }
}

#endif // !COMMAND_H