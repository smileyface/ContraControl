#ifndef ON_COMMAND_H
#define ON_COMMAND_H


#include "../command.h"

class On : public Command {
public:
	On() {};
	~On() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::ON; }
};
#endif // !ON_COMMAND_H
