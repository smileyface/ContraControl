#include "../console_log_view.h"

#include <iostream>

Console_Log_View::Console_Log_View()
{
	system_id = "Log";
}

Console_Log_View::~Console_Log_View()
{
}

void Console_Log_View::on_refresh()
{
	get_message();
}
void Console_Log_View::on_create()
{ 
	Console_View::on_create();
	Log_View_Type::create();
}

void Console_Log_View::on_display()
{
	while(!painted_messages.empty())
	{
		auto message = painted_messages.front();
		std::cout << message << std::endl << std::flush;
		painted_messages.erase(painted_messages.begin());
	}
	
}
void Console_Log_View::on_paint()
{
	while(!log_messages.empty())
	{
		auto message = log_messages.front();
		painted_messages.push_back("[" + message.LEVEL + "]\t(" + message.LOC + "):\t" + message.MESSAGE);
		log_messages.erase(log_messages.begin());
	}
}

void Console_Log_View::on_destroy()
{ 
	Console_View::on_destroy();
	Log_View_Type::destroy();
}

bool Console_Log_View::is_stale()
{
	return log_consumer->is_stale();
}

bool Console_Log_View::quit()
{
	return quiter;
}

