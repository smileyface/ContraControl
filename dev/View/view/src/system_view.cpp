#include <iostream>

#include "../console_format/console_system_view.h"

#include "Messaging/system_messaging.h"

Console_System_View::Console_System_View()
{
	system_id = "System";
	message_consumer = new Message_Consumer(stale);
	System_Messages::get_instance()->register_consumer(message_consumer);
}

void Console_System_View::display_message()
{
	std::cout << "[" << message_level << "]\t(" << system_id << "):\t" << message << std::endl << std::flush;
}

void Console_System_View::on_display()
{
	std::vector<System_Message> messages = System_Messages::get_instance()->pop(message_consumer);
	for(auto current_message = messages.begin(); current_message != messages.end(); current_message++)
	{
		message = (*current_message).message;
		system_id = (*current_message).location;
		message_level = message_priority_as_string((*current_message).priority);
		display_message();
	}
}
