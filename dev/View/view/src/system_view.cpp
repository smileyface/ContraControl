#include <iostream>

#include "../console_format/console_system_view.h"

#include "Messaging/system_messaging.h"

Console_System_View::Console_System_View()
{
	system_id = "System";
	message_consumer = new Message_Consumer(&stale);
	System_Alerts::get_instance()->register_consumer(message_consumer);
}

void Console_System_View::display_message()
{
	std::cout << "[" << message_level << "]\t(" << system_id << "):\t" << message << std::endl << std::flush;
}

void Console_System_View::on_display()
{
	std::vector<Alert> alerts = System_Alerts::get_instance()->pop(message_consumer);
	for(auto alert = alerts.begin(); alert != alerts.end(); alert++)
	{
		message = (*alert).message;
		system_id = (*alert).location;
		message_level = alert_priority_as_string((*alert).priority);
		display_message();
	}
}
