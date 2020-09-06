#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "../command.h"

class Off : public Command {
public:
 
	Off() {};
	~Off() {};
	COMMAND_ID get_unique_id() { return COMMAND_ID::OFF; };
};

#endif // !OFF_COMMAND
