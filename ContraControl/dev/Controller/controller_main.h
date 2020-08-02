
#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include <vector>
#include <algorithm>
#include <functional>

#include "../Utilities/timer.h"
#include "../Model/model_main.h"
#include "commands.h"

typedef  std::function<void()> func_ptr;

enum TIMES : uint16_t
{
	NOW = 0
};

class Timed_Command {
public:
	Timed_Command(Command* command, Device_Id device_id, double time) {
		this->command = command;
		this->device_id = device_id;
		this->time = time;
	}
	Timed_Command(Command* command, Device_Name device_name, double time) {
		this->command = command;
		this->device_id = model::known_devices[device_name]->get_id();
		this->time = time;
	}
	Command* command;
	uint16_t device_id;
	double time;
	model::Model_Command create_model_command() {
		return model::Model_Command(device_id, command);
	}
};

namespace controller
{
	Timer controller_timer;
	bool controller_running = true;
	std::vector<Timed_Command> test_commands;

	bool sort_pair(Timed_Command i, Timed_Command j) {
		return i.time < j.time;
	}

	func_ptr initalize = []() {
		std::map<std::string, Device*>::iterator it;
		for (it = model::known_devices.begin(); it != model::known_devices.end(); it++) {
			test_commands.emplace_back(Timed_Command(new Initalize(), it->second->get_id(), 0));
		}
		std::sort(test_commands.begin(), test_commands.end(), sort_pair);
		controller_timer.reset_clock();
	};


	func_ptr stop_controller = []() {
		controller_running = false;
	};

	func_ptr loop = []() {
		//while (controller_running) {
			double time = controller_timer.get_elapsed_time();
			std::vector<int> remove_indexes;
			for (int i = 0; i < test_commands.size(); i++) {
				if (test_commands[i].time <= 0)
				{
					model::Model_Command mc(test_commands[i].device_id, test_commands[i].command);
					model::add_to_step(test_commands[i].create_model_command());
					remove_indexes.push_back(i);
				}
				else {
					test_commands[i].time -= time;
				}
			}
			for (int i = remove_indexes.size()-1; i >-1  ; i--) {
				test_commands.erase(test_commands.begin() + remove_indexes[i]);
			}
			controller_timer.update_time();

		//}
	};



}



#endif