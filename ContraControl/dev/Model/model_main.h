#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <vector>
#include <string>

#include "devices.h"
#include "../Utilities/timer.h"


namespace model {
	class Model_Command {
	public:
		Model_Command(Device_Id id, Command* command){
			this->command = command;
			this->id = id;
		}
		Device_Id id; 
		Command* command;
	};

	Timer timer;
	std::map<Device_Name, Device*> known_devices;
	bool model_running = true;

	std::vector<Model_Command> step_run;
	std::map<Device_Id, Device_Name> id_map;


	std::function<void()> initalize = []() {
		std::map<Device_Name, Device*>::iterator it;
		for (it = known_devices.begin(); it != known_devices.end(); it++) {
			id_map[it->second->get_id()] = it->first;
		}

	};

	std::function<void(Model_Command)> add_to_step = [](Model_Command theCommand) {
		model::step_run.emplace_back(theCommand);
	};

	std::function<void()> loop = []() {
		//while (model_running) {
		std::vector<int> completed_index;
		for (int i = 0; i < step_run.size(); i++) {
			known_devices[id_map[step_run[i].id]]->run_command(step_run[i].command);
			if (step_run[i].command->time_to_complete <= 0) {
				completed_index.push_back(i);
			}
			else {
				step_run[i].command->time_to_complete -= model::timer.elapsed_time;
			}
		}
		for (int i = completed_index.size(); i > 0; i--) {
			model::step_run.erase(step_run.begin() + completed_index[i-1]);
		}
		timer.update_time();

		//}
	};

	std::function<void()> stop_loop = []() {
		model_running = false;
	};



}
#endif 