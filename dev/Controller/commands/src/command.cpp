#include "../command.h"

Command::Command() : 
	complete(false)
{ }


COMMAND_ENUM Command::get_id() 
{ 
	return COMMAND_ENUM::INVALID; 
}

bool Command::completed() 
{ 
	return complete;
}

void Command::complete_command()
{
	complete = true;
}
