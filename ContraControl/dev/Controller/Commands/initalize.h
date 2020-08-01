#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include "command.h"

class Initalize : public Command
{
	const static COMMAND_ID unique_id = COMMAND_ID::INITALIZE;
	Initalize();
	~Initalize() {};
};
#endif // !INITALIZE_COMMAND_H