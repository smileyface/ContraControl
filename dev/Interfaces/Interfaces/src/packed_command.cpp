#include <utility>

#include "../types/packed_command.h"

Packed_Command::Packed_Command() :
	command(0),
	time(0.0),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(const Packed_Command& cmd) noexcept :
	command(cmd.command),
	device_label(cmd.device_label),
	time(cmd.time),
	run(cmd.run),
	sent(cmd.sent)
{ }

Packed_Command::Packed_Command(Packed_Command&& cmd) :
	command(nullptr),
	time(0.0),
	run(false),
	sent(false)
{ 
	this->command = cmd.command;
	this->device_label = cmd.device_label;
	this->time = cmd.time;
	this->run = cmd.run;
	this->sent = cmd.sent;

	cmd.command = nullptr;
	cmd.device_label = Device_Label();
	cmd.time = 0.0;
	cmd.run = false;
	cmd.sent = false;

}

Packed_Command::Packed_Command(Command* cmd, Device_Label label, double time) :
	command(cmd),
	device_label(std::move(label)),
	time(time),
	run(false),
	sent(false)
{ }

Packed_Command::~Packed_Command()
{ }

Packed_Command& Packed_Command::operator=(const Packed_Command& cmd) noexcept
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

Packed_Command& Packed_Command::operator=(Packed_Command&& cmd) noexcept
{
	if(this != &cmd)
	{
		delete this->command;

		this->command = cmd.command;
		this->device_label = cmd.device_label;
		this->time = cmd.time;
		this->run = cmd.run;
		this->sent = cmd.sent;

		cmd.command = nullptr;
		cmd.device_label = Device_Label();
		cmd.time = 0.0;
		cmd.run = false;
		cmd.sent = false;
	}
	return *this;
}
