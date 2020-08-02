#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <vector>
#include <string>

#include "devices.h"
#include "../Utilities/timer.h"


namespace model {
	Timer timer;
	std::map<Device_Name, Device*> known_devices;
	bool model_running = true;

	std::map<Device_Id, Command> step_run;
	std::map<Device_Id, Device_Name> id_map;


	std::function<void()> initalize = []() {
		std::map<Device_Name, Device*>::iterator it;
		for (it = known_devices.begin(); it != known_devices.end(); it++) {
			id_map[it->second->get_id()] = it->first;
		}

	};

	std::function<void(std::pair<Device_Id, Command>)> add_to_step = [](std::pair<Device_Id, Command> theCommand) {
		model::step_run.emplace(theCommand);
	};

	std::function<void()> loop = []() {
		//while (model_running) {
		std::map<Device_Id, Command>::iterator it;
		std::vector<Device_Id> completed_list;
		for (it = step_run.begin(); it != step_run.end(); it++) {
			known_devices[id_map[it->first]]->run_command(it->second);
			if (it->second.time_to_complete <= 0) {
				completed_list.push_back(it->first);
			}
			else {
				it->second.time_to_complete -= model::timer.elapsed_time;
			}
		}
		for (int i = 0; i < completed_list.size(); i++) {
			model::step_run.erase(completed_list[i]);
		}
		timer.update_time();

		//}
	};

	std::function<void()> stop_loop = []() {
		model_running = false;
	};



}
#endif 