#ifndef INITALIZE_COMMAND_H
#define INITALIZE_COMMAND_H

#include "../command.h"
#include <string>

class Initalize : public Command
{
public:
	Initalize(std::string new_name) 
	{ 
		name = new_name; 
	};

	~Initalize() {};
	std::string name;
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::INITALIZE; }
};
#endif // !INITALIZE_COMMAND_H