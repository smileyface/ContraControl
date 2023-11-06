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
	Packed_Command id = cmd;
	LOG_DEBUG("Command " + id.get_command()->get_id_str() + " added to controller");
	controller_queue.push_back(cmd);
}

void controller::step()
{
	for(auto command = controller_queue.begin(); command != controller_queue.end(); command++)
  {
		Packed_Command& step_command = (*command);
		controller_task.add_subtask(Cleaned_Task([&step_command] () mutable
									{
										controller_mutex.lock();
										LOG_DEBUG("Sending Command " + step_command.get_command()->get_id_str() +" to the Model")
										if(!step_command.command_sent() && step_command.get_time() <= 0)
										{
											Message_Relay::get_instance()->push(new Controller_Model_Command((step_command)));
											step_command.send_command();
										}
										else
										{
											step_command.move_time(controller_timer.get_elapsed_time());
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