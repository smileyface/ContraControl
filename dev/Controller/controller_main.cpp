#include <algorithm>    // std::sort

#include "controller_main.h"
#include "Interfaces/controller_interface.h"

#include <thread>
#include <mutex>

std::thread controller_thread;
std::mutex controller_mutex;

Timer controller_timer;
bool controller::controller_running = true;
Timed_List controller::controller_queue;

System_Messages* controller::controller_message_interface;


void controller::initalize()
{
	controller_timer.reset_clock();
	controller_message_interface = System_Messages::get_instance();
}
 
void controller_loop()
{
	controller::controller_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG, "Loop thread has started", "Controller"));
	while (controller::controller_running)
	{
		controller::step();
	}
}
void controller::start_controller()
{
	controller_message_interface->push(System_Message(MESSAGE_PRIORITY::INFO, "Controller Started", subsystem_name));
	controller_thread = std::thread(controller_loop);
}

void controller::stop_controller()
{
	controller_message_interface->push(System_Message(MESSAGE_PRIORITY::INFO, "Controller Stopped", subsystem_name));
	controller_running = false;
	if(controller_thread.joinable())
		controller_thread.join();
}

void controller::add_command(Timed_Command tc)
{
	controller_mutex.lock();
	controller::controller_queue.push_back(tc);
	controller_mutex.unlock();
	std::sort(controller::controller_queue.begin(), controller::controller_queue.end(), [](Timed_Command a, Timed_Command b) {
		return a < b;
		});
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
