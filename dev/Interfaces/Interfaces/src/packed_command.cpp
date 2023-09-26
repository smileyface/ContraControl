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


Packed_Command::~Packed_Command()
{

}

void Packed_Command::move_time(double elapsed_time)
{
	time -= elapsed_time;
}

double Packed_Command::get_time()
{
	return time;
}

Command* Packed_Command::get_command()
{
	return command;
}
bool Packed_Command::command_run()
{
	return run;
}

bool Packed_Command::command_sent()
{
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
