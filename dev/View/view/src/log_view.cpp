#include <iostream>

#include "../console_format/console_log_view.h"
#include "../view_type/log_view_type.h"

#include "Messaging/message_relay.h"

Log_View_Type::Log_View_Type()
{
	log_consumer = new Message_Consumer(log_stale, new Logging_Message());
	Message_Relay::get_instance()->register_consumer(log_consumer);
}
void Log_View_Type::get_message()
{
	Logging_Message* messages = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(log_consumer));
	message.MESSAGE = messages->get_message();
	message.LOC = messages->get_location();
	message.LEVEL = messages->get_priority_string();
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
}
void Console_Log_View::on_display()
{
	std::cout << painted_message << std::endl << std::flush;
}
void Console_Log_View::on_paint()
{
	painted_message = "[" + message_level + "]\t(" + system_id + "):\t" + message_;
}