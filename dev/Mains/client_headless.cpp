#include <iostream>

#include "Interfaces/main_interface.h"
int main()
{
	std::cout << "RUNNING HEADLESS CLIENT";
	Main_Interfaces::Controller_Interface::start_controller();
	Main_Interfaces::View_Interface::add_display(DISPLAY_TYPES::CONSOLE);
	Main_Interfaces::View_Interface::start_view();
	return 0;
}
