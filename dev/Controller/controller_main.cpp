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

void controller::add_command(Packed_Command& cmd)
{
	controller_queue.push_back(cmd);
}

void controller::step()
{
	for(auto command = controller_queue.begin(); command != controller_queue.end(); command++)
  {
		controller_task.add_subtask(Cleaned_Task([command] () mutable
									{
										controller_mutex.lock();
										if(!command->command_sent() && command->get_time() <= 0)
										{
											Message_Relay::get_instance()->push(new Controller_Model_Command((*command)));
											command->send_command();
										}
										else
										{
											command->move_time(controller_timer.get_elapsed_time());
										}
										controller_mutex.unlock();
									}));

	}
	controller_timer.update_time();


}

void controller::clean_up()
{
	Commander::destroy_instance();
	controller_queue.clear();
}