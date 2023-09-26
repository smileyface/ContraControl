#include <algorithm>    // std::sort

#include "controller_main.h"

#include <thread>
#include <mutex>

std::mutex controller_mutex;

Timer controller_timer;
bool controller::controller_running = true;
Command_List controller::controller_queue;
Task controller::controller_task;

//FILE GLOBALS
std::vector<int> remove_indexes;

void controller::initalize()
{
	controller_timer.reset_clock();
	controller_task = Task("Controller", 2, .15);
	Scheduler::get_instance()->add_system_task(controller::step);
	Scheduler::get_instance()->add_cleanup_task([] ()
												{
													for(auto command = controller::controller_queue.begin(); command != controller::controller_queue.end();)
													{
														controller_mutex.lock();
														if(command->command_sent())
														{
															command = controller::controller_queue.erase(command);
														}
														else
														{
															command++;
														}
														controller_mutex.unlock();
													}
													Commander::get_instance()->clean_list();
												});
}
void controller::start_controller()
{
	controller_running = true;
	controller_timer.start_clock();
	LOG_INFO("Controller Added to the Scheduler", subsystem_name);
	Scheduler::get_instance()->add_task(&controller::controller_task);
}

void controller::stop_controller()
{
	LOG_INFO("Controller Stopped", subsystem_name);
	controller_task.set_persistence(false);
	controller_running = false;
}

void controller::add_command(const Packed_Command& cmd)
{
	controller_queue.push_back(cmd);
}

void controller::step()
{
	for(int i = 0; i < controller_queue.size(); i++)
	{
		if(!controller_queue[i].command_sent() && controller_queue[i].get_time() <= 0)
		{
			controller_task.add_subtask(Cleaned_Task([i] ()
										{
											try
											{
												Message_Relay::get_instance()->push(new Controller_Model_Command(controller::controller_queue[i]));
											}
											catch(std::exception&)
											{
												controller::controller_task.exception(std::current_exception());
											}
										}));
			controller_queue[i].send_command();
		}
		else
		{
			controller::controller_queue[i].move_time(controller_timer.get_elapsed_time());
		}
	}
	controller_timer.update_time();


}

void controller::clean_up()
{
	Commander::destroy_instance();
	controller_queue.clear();
}