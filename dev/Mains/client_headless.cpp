#include <iostream>

#include "Interfaces/main_interface.h"


bool program_running;

void start_program()
{
	std::cout << "RUNNING HEADLESS CLIENT" << std::endl;
	program_running = true;
	Main_Interfaces::Controller_Interface::start_controller();
	Main_Interfaces::Model_Interface::start_model();
	Main_Interfaces::View_Interface::add_view(0);
	Main_Interfaces::View_Interface::start_view();
}

void exit_program()
{
	std::cout << "STOPPING HEADLESS CLIENT" << std::endl;
	program_running = false;
	Main_Interfaces::Controller_Interface::stop_controller();
	Main_Interfaces::Model_Interface::stop_model();
	Main_Interfaces::View_Interface::stop_view();
}


int main()
{
	start_program();
	while (program_running)
	{
		char keyboard_signal = '\n';
		std::cin >> keyboard_signal;

		if (keyboard_signal == 'x')
		{
			exit_program();
		}
	}
	return 0;
}
