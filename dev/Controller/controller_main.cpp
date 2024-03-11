#include <algorithm>    // std::sort

#include "controller_main.h"

#include <thread>
#include <mutex>

std::mutex controller_mutex;

Timer controller_timer;

Controller* Controller::instance = 0;

//FILE GLOBALS
std::vector<int> remove_indexes;
void controller_step()
{
	Controller::get_instance()->step();
}

Controller::Controller()
{
	controller_timer.reset_clock();
	controller_task = Task("Controller", 2, .15);
	Scheduler::get_instance()->add_system_task(controller_step);
	Scheduler::get_instance()->add_cleanup_task([this] ()
												{
													for(auto command = controller_queue.begin(); command != controller_queue.end();)
													{
														controller_mutex.lock();
														if(command->command_sent())
														{
															command = controller_queue.erase(command);
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

Controller ::~Controller()
{
	Commander::destroy_instance();
	controller_queue.clear();
	LOG_INFO("Controller Destroyed", "Controller");
}

Controller* Controller::get_instance()
{
	if (instance == 0)
	{
		instance = new Controller();
	}
	return instance;
}

void Controller::destroy_instance()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

void Controller::start_loop()
{
	controller_running = true;
	controller_timer.start_clock();
	LOG_INFO("Controller Added to the Scheduler", subsystem_name());
	Scheduler::get_instance()->add_task(&controller_task);
}

void Controller::stop_loop()
{
	LOG_INFO("Controller Stopped", subsystem_name());
	controller_task.set_persistence(false);
	controller_running = false;
}

void Controller::add_command(const Packed_Command& cmd)
{
	Packed_Command id = cmd;
	LOG_DEBUG("Command " + id.get_command()->get_id_str() + " added to controller");
	controller_queue.push_back(cmd);
}

void Controller::step()
{
	for(auto command = controller_queue.begin(); command != controller_queue.end(); command++)
  {
		Packed_Command& step_command = (*command);
		controller_task.add_subtask(Cleaned_Task([&step_command] () mutable
									{
										controller_mutex.lock();
										if(!step_command.command_sent() && step_command.get_time() <= 0)
										{
											LOG_DEBUG("Sending Command " + step_command.get_command()->get_id_str() + " to the Model")
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
