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
	message_ = message.MESSAGE;
	system_id = message.LOC;
	message_level = message.LEVEL;
	message_valid = message.vaild;
}
void Console_Log_View::on_create()
{ 
	Console_View::on_create();
	Log_View_Type::create();
}

void Console_Log_View::on_display()
{
	std::cout << painted_message << std::endl << std::flush;
}
void Console_Log_View::on_paint()
{
	painted_message = "[" + message_level + "]\t(" + system_id + "):\t" + message_;
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

