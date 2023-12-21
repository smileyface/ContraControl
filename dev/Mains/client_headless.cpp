#include <iostream>



bool program_running;

void start_program()
{
	std::cout << "RUNNING HEADLESS CLIENT" << std::endl;
	program_running = true;
}

void exit_program()
{
	std::cout << "STOPPING HEADLESS CLIENT" << std::endl;
	program_running = false;
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
