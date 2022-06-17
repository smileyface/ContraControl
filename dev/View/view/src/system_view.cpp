#include <iostream>

#include "../console_format/console_system_view.h"

#include "Messaging/message_relay.h"

Console_Log_View::Console_Log_View()
{
	system_id = "System";
	message_consumer = new Message_Consumer(stale, new Logging_Message());
	Message_Relay::get_instance()->register_consumer(message_consumer);
}

void Console_Log_View::on_refresh()
{
	Logging_Message* messages = dynamic_cast<Logging_Message*>(Message_Relay::get_instance()->pop(message_consumer));
	message = messages->get_message();
	system_id = messages->get_location();
	message_level = messages->get_priority_string();
}
void Console_Log_View::on_display()
{
	std::cout << painted_message << std::endl << std::flush;
}
void Console_Log_View::on_paint()
{
	painted_message = "[" + message_level + "]\t(" + system_id + "):\t" + message;
}