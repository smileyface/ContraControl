#include "../types/packed_command.h"

Packed_Command::Packed_Command() :
	command(0),
	device_label(),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label, double time) :
	command(cmd),
	device_label(label),
	time(time),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label) :
	command(cmd),
	device_label(label),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::~Packed_Command()
{ }



bool Packed_Command::operator<(const Packed_Command& cmd)
{
	return time < cmd.time;
}

void Packed_Command::operator=(const Packed_Command& cmd)
{
	command = cmd.command;
	device_label = cmd.device_label;
	time = cmd.time;
	run = cmd.run;
}
