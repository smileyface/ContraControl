#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <string>

#include"device.h"
#include "devices/switch_device.h"


namespace model {
	std::map<std::string, Device*> known_devices;
	bool model_running = true;
	float timestamp;

	std::map<uint16_t, Command> step_run;
	std::map<uint16_t, std::string> id_map;

	std::function<void()> read_program = []() {
		known_devices["Device_1"] = new SwitchDevice();
	};

	std::function<void()> initalize = []() {
		read_program();
		std::map<std::string, Device*>::iterator it;
		for (it = known_devices.begin(); it != known_devices.end(); it++) {
			it->second->initalize();
		}
		//common_id to system_id mapping
		for (it = known_devices.begin(); it != known_devices.end(); it++) {
			id_map[it->second->get_id()] = it->first;
		}
	};

	std::function<void()> loop = []() {
		model::initalize();
		while (model_running) {
			int start_time = 0;
			std::map<uint16_t, Command>::iterator it;
			for (it = step_run.begin(); it != step_run.end(); it++) {
				known_devices[id_map[it->first]]->run_command(it->second);
			}
			timestamp = 0 - start_time;

		}
	};

	std::function<void()> stop_loop = []() {
		model_running = false;
	};



}
#endif 