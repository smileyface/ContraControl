#ifndef COMMAND_H
#define COMMAND_H

#include <utility>

#include <cinttypes>

enum class COMMAND_ID :uint16_t
{
	//System Commands
	ADD,
	REMOVE,
	//Device Commands
	INITALIZE,
	ON,
	OFF,
	MOVE,
	INVALID = UINT16_MAX
};

const std::pair<COMMAND_ID, COMMAND_ID> SYSTEM_COMMANDS_INDEXES(COMMAND_ID::ADD, COMMAND_ID::REMOVE);
const std::pair<COMMAND_ID, COMMAND_ID> DEVICE_COMMANDS_INDEXES(COMMAND_ID::INITALIZE, COMMAND_ID::MOVE);

class Command {
public:
	
	double time_to_complete = 0.0;
	Command() { };
	~Command() {};
	virtual COMMAND_ID get_unique_id() { return COMMAND_ID::INVALID; };
private:
};

#endif // !COMMAND_H