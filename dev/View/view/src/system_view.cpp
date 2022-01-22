#include <iostream>

#include "../console_format/console_system_view.h"

#include "Alerts/system_alerts.h"

void Console_System_View::notify()
{
	stale = true;
}

void Console_System_View::display_message()
{
	std::cout << "[" << message_level << "]\t(" << system_id << "):\t" << message << std::endl;
}

void Console_System_View::on_display()
{
	for(Alert alert = System_Alerts::get_instance()->pop(); alert.valid_alert == true; alert = System_Alerts::get_instance()->pop())
	{
		message = alert.message;
		system_id = alert.location;
		message_level = alert_priority_as_string(alert.priority);
		display_message();
	}
	stale = false;
}
