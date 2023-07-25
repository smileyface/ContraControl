#include <iostream>

#include "../console_format/console_log_view.h"
#include "../view_type/log_view_type.h"

#include "Messaging/message_relay.h"

Log_View_Type::Log_View_Type()
{
	log_consumer =	Message_Relay::get_instance()->register_consumer<Logging_Message>();
}
void Log_View_Type::get_message()
{
	Logging_Message messages = Message_Relay::get_instance()->pop<Logging_Message>(log_consumer);
	message.MESSAGE = messages.get_message();
	message.LOC = messages.get_location();
	message.LEVEL = messages.get_priority_string();
	message.vaild = message.MESSAGE == "" ? false: true;
}
void Log_View_Type::destroy()
{ 
	Message_Relay::get_instance()->deregister_consumer(log_consumer);
}
Console_Log_View::Console_Log_View()
{
	system_id = "Log";
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

}

void Console_Log_View::on_display()
{
	if(message_valid)
	{
		std::cout << painted_message << std::endl << std::flush;
	}
}
void Console_Log_View::on_paint()
{
	painted_message = "[" + message_level + "]\t(" + system_id + "):\t" + message_;
}

void Console_Log_View::on_destroy()
{
	Log_View_Type::destroy();
	Console_View::on_destroy();
}

bool Console_Log_View::is_stale()
{
	return log_consumer->is_stale();
}

bool Console_Log_View::quit()
{
	return quiter;
}
