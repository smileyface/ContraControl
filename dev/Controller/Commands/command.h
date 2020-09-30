#ifndef COMMAND_H
#define COMMAND_H

#include <utility>

#include <cinttypes>
#include <string>
#include <typeinfo>

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
	bool completed() { return time_to_complete <= 0.0; }
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INVALID; }
	virtual std::string get_unique_id() 
	{
		switch (get_id())
		{
		case COMMAND_ENUM::INITALIZE:
			return "INITALIZE";
		case COMMAND_ENUM::ON:
			return "ON";
		case COMMAND_ENUM::OFF:
			return "OFF";
		}
		return "INVALID"; 
	}
private:
};

#endif // !COMMAND_H