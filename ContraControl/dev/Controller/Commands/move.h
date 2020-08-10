#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "command.h"

class Move : public Command
{
public:
	Move() { };
	~Move() { };
	COMMAND_ID get_unique_id() { return COMMAND_ID::MOVE; };
	float amount = 0.0;
};
#endif // !MOVE_COMMAND_H