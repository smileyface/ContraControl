#include <utility>

#include "../types/packed_command.h"

Packed_Command::Packed_Command() :
	command(0),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(Command* cmd, double time) :
	command(cmd),
	time(time),
	run(false),
	sent(false)
{ }

Packed_Command::~Packed_Command()
{
//	delete command;
}

