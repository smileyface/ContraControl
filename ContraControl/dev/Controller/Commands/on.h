#include "command.h"

class On : public Command {
	const static COMMAND_ID unique_id = COMMAND_ID::ON;
	On();
	~On() {};
};