#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include "command.h"
#include <string>

class Initalize : public Command
{
public:
	Initalize(std::string new_name) 
	{ 
		name = new_name; 
	};

	~Initalize() {};
	COMMAND_ID get_unique_id() { return COMMAND_ID::INITALIZE; };
	std::string name;
};
#endif // !INITALIZE_COMMAND_H