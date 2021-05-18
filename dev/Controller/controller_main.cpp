#include <algorithm>    // std::sort

#include "controller_main.h"
#include "../Interfaces/controller_interface.h"


Timer controller_timer;
bool controller::controller_running = true;
std::vector<Timed_Command> controller::controller_queue;

void controller::initalize()
{
	controller_timer.reset_clock();
}

void controller::stop_controller()
{
	controller_running = false;
}

void controller::add_command(Timed_Command tc)
{
	controller::controller_queue.push_back(tc);
	std::sort(controller::controller_queue.begin(), controller::controller_queue.end());
}

void controller::step()
{
	std::vector<int> remove_indexes;
	for (int i = 0; i < controller_queue.size(); i++) 
	{
		if (controller_queue[i].time <= 0)
		{
			Controller_Interfaces::Model_Interface::send_command(controller_queue[i]);
			if (controller_queue[i].command->completed())
				remove_indexes.push_back(i);
		}
		else {
			controller_queue[i].time -= controller_timer.get_elapsed_time();
		}
	}
	for (size_t i = 0; i < remove_indexes.size(); i++) 
	{
		controller_queue.erase(controller_queue.begin() + remove_indexes[i]);
	}
	controller_timer.update_time();
}

void controller::clean_up()
{
	controller_queue.erase(controller_queue.begin(), controller_queue.end());
}
