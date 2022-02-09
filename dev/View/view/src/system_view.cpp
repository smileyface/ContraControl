#include <iostream>

#include "../console_format/console_system_view.h"

#include "Messaging/system_messaging.h"

Console_System_View::Console_System_View()
{
	system_id = "System";
	message_consumer = new Message_Consumer(stale);
	System_Messages::get_instance()->register_consumer(message_consumer);
}

void Console_System_View::on_refresh()
{
	System_Message messages = System_Messages::get_instance()->pop(message_consumer);
	message = messages.message;
	system_id = messages.location;
	message_level = message_priority_as_string(messages.priority);
}
void Console_System_View::on_display()
{
	std::cout << painted_message << std::endl << std::flush;
}
void Console_System_View::on_paint()
{
	painted_message = "[" + message_level + "]\t(" + system_id + "):\t" + message;
}
