#include <iostream>

#include "../console_format/console_system_view.h"
void Console_System_View::notify()
{
	stale = true;
}

void Console_System_View::display_message(std::string message)
{
	message = message;
	notify();
}

void Console_System_View::on_display()
{
	std::cout << "(" << system_id << "): " << message << std::endl;
}
