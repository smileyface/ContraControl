#include <iostream>

#include "Interfaces/main_interface.h"
int main()
{
	std::cout << "RUNNING HEADLESS CLIENT" << std::endl;
	Main_Interfaces::Controller_Interface::start_controller();
	Main_Interfaces::Model_Interface::start_model();
	Main_Interfaces::View_Interface::initalize({ DISPLAY_TYPES::CONSOLE });
	Main_Interfaces::View_Interface::start_view();
	return 0;
}
