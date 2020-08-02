#ifndef ON_COMMAND_H
#define ON_COMMAND_H


#include "command.h"

class On : public Command {
public:
	const static COMMAND_ID unique_id = COMMAND_ID::ON;
	On() {};
	~On() {};
};
#endif // !ON_COMMAND_H
