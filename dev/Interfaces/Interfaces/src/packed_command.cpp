#include <utility>

#include "../types/packed_command.h"

Packed_Command::Packed_Command() :
	command(0),
	device_label(Device_Label()),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(const Packed_Command& cmd) :
	command(cmd.command),
	device_label(cmd.device_label),
	time(cmd.time),
	run(cmd.run),
	sent(cmd.sent)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label, double time) :
	command(cmd),
	device_label(std::move(label)),
	time(time),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(Command* cmd, Device_Label label) :
	command(cmd),
	device_label(std::move(label)),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::~Packed_Command()
{ }



bool Packed_Command::operator<(const Packed_Command& cmd) const
{
	return time < cmd.time;
}

Packed_Command& Packed_Command::operator=(const Packed_Command& cmd)
{
	if(this != &cmd)
	{
		this->command = cmd.command;
		this->device_label = cmd.device_label;
		this->time = cmd.time;
		this->run = cmd.run;
	}
	return *this;
}
