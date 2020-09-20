#ifndef OFF_COMMAND
#define OFF_COMMAND

#include "../command.h"

class Off : public Command {
public:
 
	Off() {};
	~Off() {};
	COMMAND_ID get_unique_id() { return COMMAND_ID::OFF; };
	std::string get_log_entry() { return "Turned Off"; };
};

#endif // !OFF_COMMAND
