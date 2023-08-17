#include "../types/packed_command.h"

Packed_Command::Packed_Command() :
	command(0),
	device_label(),
	time(0.0),
	run(false)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label, double t) :
	command(cmd),
	device_label(label),
	time(t),
	run(false)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label) :
	command(cmd),
	device_label(label),
	time(0.0),
	run(false)
{ }

Packed_Command::~Packed_Command()
{ }



bool Packed_Command::operator<(const Packed_Command& tc)
{
	return time < tc.time;
}

void Packed_Command::operator=(const Packed_Command& tc)
{
	command = tc.command;
	device_label = tc.device_label;
	time = tc.time;
	run = tc.run;
}
