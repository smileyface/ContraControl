#ifndef ON_COMMAND_H
#define ON_COMMAND_H


#include "../command.h"

class On : public Command {
public:
	On() {};
	~On() {};
	COMMAND_ID get_unique_id() { return COMMAND_ID::ON; };
};
#endif // !ON_COMMAND_H
