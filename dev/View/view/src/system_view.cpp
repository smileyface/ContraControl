#include <iostream>

#include "../Views/system.h"
void System_View::notify()
{
	on_display();
}
void System_View::notify_with_message(char* msg)
{
}
void System_View::on_display()
{
	std::cout << "(" << system_id << ")";
}
