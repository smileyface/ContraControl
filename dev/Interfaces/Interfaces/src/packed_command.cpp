#include <utility>

#include "../types/packed_command.h"

Packed_Command::Packed_Command() :
	command(0),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label, double time) :
	command(cmd),
	device_label(std::move(label)),
	time(time),
	run(false),
	sent(false)
{ }

Packed_Command::~Packed_Command()
{
//	delete command;
}

