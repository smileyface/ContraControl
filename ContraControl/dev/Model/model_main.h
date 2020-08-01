#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

#include <map>
#include <string>

#include"devices.h"


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
	};


	std::function<void()> loop = []() {
		while (model_running) {
			float start_time = 0.0;
			std::map<uint16_t, Command>::iterator it;
			for (it = step_run.begin(); it != step_run.end(); it++) {
				known_devices[id_map[it->first]]->run_command(it->second);
			}
			timestamp = 0.0 - start_time;

		}
	};

	std::function<void()> stop_loop = []() {
		model_running = false;
	};



}
#endif 