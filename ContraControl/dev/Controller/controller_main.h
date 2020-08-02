
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



namespace controller
{
	Timer controller_timer;
	bool controller_running = true;
	std::vector<Timed_Command> test_commands;

	bool sort_pair(Timed_Command i, Timed_Command j) {
		return i.first < j.first;
	}

	func_ptr initalize = []() {
		std::map<std::string, Device*>::iterator it;
		for (it = model::known_devices.begin(); it != model::known_devices.end(); it++) {

			test_commands.emplace_back(std::make_pair(0, std::make_pair(it->second->get_id(), Initalize())));
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
				if (test_commands[i].first <= 0)
				{
					model::add_to_step(test_commands[i].second);
					remove_indexes.push_back(i);
				}
				else {
					test_commands[i].first -= time;
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