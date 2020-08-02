#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include "command.h"

class Initalize : public Command
{
public:
	Initalize() { };
	~Initalize() {};
	COMMAND_ID get_unique_id() { return COMMAND_ID::INITALIZE; };
};
#endif // !INITALIZE_COMMAND_H