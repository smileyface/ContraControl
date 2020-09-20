#ifndef COMMAND_H
#define COMMAND_H

#include <utility>

#include <cinttypes>
#include <string>


enum class COMMAND_ID : uint16_t
{
	//System Commands
	ADD,
	REMOVE,
	INITALIZE,
	ON,
	OFF,
	TRANSITION,
	INVALID = UINT16_MAX
};


class Command {
public:
	
	double time_to_complete = 0.0;
	Command() { };
	~Command() {};
	virtual void step_command(double time_step) { }
	bool completed() { return time_to_complete <= 0.0; }
	virtual COMMAND_ID get_unique_id() { return COMMAND_ID::INVALID; };
	virtual std::string get_log_entry() { return "ERROR: INVALID COMMAND"; };
private:
};

#endif // !COMMAND_H