#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "../command.h"

class Off : public Command {
public:
 
	Off() {};
	~Off() {};
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::OFF; }
};

#endif // !OFF_COMMAND
