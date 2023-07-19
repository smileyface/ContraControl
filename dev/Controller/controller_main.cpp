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
Task controller::controller_task;

//FILE GLOBALS
std::vector<int> remove_indexes;

void controller_loop()
{
	LOG_DEBUG("Loop thread has started");
	while(controller::controller_running)
	{
		controller::step();
	}
}
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
														if(command->command->completed())
														{
															command = controller::controller_queue.erase(command);
														}
														else
														{
															command++;
														}
														controller_mutex.unlock();
													}
												});
}
void controller::start_controller()
{
	controller_running = true;
	LOG_INFO("Controller Added to the Scheduler", subsystem_name);
	Scheduler::get_instance()->add_task(&controller::controller_task);
}

void controller::stop_controller()
{
	LOG_INFO("Controller Stopped", subsystem_name);
	controller_task.set_persistence(false);
	controller_running = false;
}

void controller::add_command(Timed_Command tc)
{
	controller_mutex.lock();
	controller::controller_queue.push_back(tc);
	controller_mutex.unlock();
	std::sort(controller::controller_queue.begin(), controller::controller_queue.end(), [] (Timed_Command a, Timed_Command b)
			  {
				  return a < b;
			  });
}

void controller::step()
{
	for(int i = 0; i < controller_queue.size(); i++)
	{
		if(controller_queue[i].run == false)
		{
			controller_task.add_subtask(Cleaned_Task([i] ()
										{
											try
											{
												if(controller::controller_queue[i].time <= 0)
												{
													Controller_Interfaces::Model_Interface::send_command(controller::controller_queue[i]);
												}
												else
												{
													controller::controller_queue[i].time -= controller_timer.get_elapsed_time();
												}
											}
											catch(std::exception&)
											{
												controller::controller_task.exception(std::current_exception());
											}

										}));
			controller::controller_queue[i].run = true;
		}
	}


}

void controller::clean_up()
{
	controller_queue.clear();
}