#include "command.h"

class Off : public Command {
public:
	const static COMMAND_ID unique_id = COMMAND_ID::OFF;
	Off() {};
	~Off() {};
};
