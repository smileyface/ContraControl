#include <algorithm>    // std::sort

#include "controller_main.h"

#include <thread>
#include <mutex>

std::mutex controller_mutex;

Timer controller_timer;

Controller* Controller::instance = 0;

//FILE GLOBALS
std::vector<int> remove_indexes;

void Controller::cleanup_task() {
	for (auto command = controller_queue.begin(); command != controller_queue.end();)
	{
		controller_mutex.lock();
		if (command->command_sent())
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
}

Controller::Controller()
{
	controller_timer.reset_clock();
	controller_task = Task("Controller", 2, .15);
	Scheduler::get_instance()->add_system_task(std::bind(&Controller::step, this));
	Scheduler::get_instance()->add_cleanup_task(std::bind(&Controller::cleanup_task, this));
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

char* Controller::subsystem_name() const
{
	return (char*)"Controller";
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
	std::lock_guard<std::mutex> lock(controller_mutex);
	LOG_DEBUG("Command " + cmd.get_command()->get_id_str() + " added to controller");
	controller_queue.emplace_back(cmd);
}

void Controller::step()
{
	// Iterate over the controller queue
	for (auto& step_command : controller_queue) {
		// Create a lambda function for executing the step command
		auto step_task = [&step_command, this]() {
				controller_mutex.lock();
				if (!step_command.command_sent() && step_command.get_time() <= 0) 
				{
					//If the command has not been sent, and is ready to be sent, send it.
					LOG_DEBUG("Sending Command " + step_command.get_command()->get_id_str() + " to the Model");
					Message_Relay::get_instance()->push(new Controller_Model_Command(step_command));
					step_command.send_command();
				}
				else if (step_command.command_sent())
				{
					//Clean task happens on a different priority
					//Left blank intentionally
				}
				else {
					step_command.move_time(controller_timer.get_elapsed_time());
				}
				controller_mutex.unlock();
			};

		// Add the step task to the scheduler as a subtask
		controller_task.add_subtask(Cleaned_Task(step_task));
		//update the controller timer.
		controller_timer.update_time();
	}

}
