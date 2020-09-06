#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "../command.h"

class Level : public Command
{
public:
	Level() { };
	~Level() { };
	COMMAND_ID get_unique_id() { return COMMAND_ID::LEVEL; };
	float amount = 0.0;
};
#endif // !MOVE_COMMAND_H