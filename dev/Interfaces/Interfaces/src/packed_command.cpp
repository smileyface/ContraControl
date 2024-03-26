#include <utility>

#include "../types/packed_command.h"



Packed_Command::Packed_Command() :
	command(0),
	time(0.0),
	run(false),
	sent(false)
{
}

Packed_Command::Packed_Command(Command* cmd, double time) :
	command(cmd),
	time(time),
	run(false),
	sent(false)
{ }

Packed_Command::Packed_Command(const Packed_Command& cmd) :
	command(cmd.command),
	time(cmd.time),
	run(cmd.run),
	sent(cmd.sent)
{ }

Packed_Command::~Packed_Command()
{

}

void Packed_Command::move_time(double elapsed_time)
{
	time -= elapsed_time;
}

double Packed_Command::get_time() const
{
	return time;
}

Command* Packed_Command::get_command() const {
	return command;
}

bool Packed_Command::command_run() const {
	return run;
}

bool Packed_Command::command_sent() const {
	return sent;
}

void Packed_Command::send_command()
{ 
	sent = true;
}

void Packed_Command::run_command()
{
	run = true;
}

bool Packed_Command::operator==(const Packed_Command& rhs) const
{
	// Implement your comparison logic here
	// For example, compare relevant members of Packed_Command
	return get_command() == rhs.get_command();
}