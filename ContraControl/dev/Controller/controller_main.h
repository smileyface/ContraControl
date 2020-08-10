
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
	extern Timer controller_timer;
	extern bool controller_running;
	extern std::vector<Timed_Command> test_commands;

	bool sort_pair(Timed_Command i, Timed_Command j);

	void initalize();
	void stop_controller();

	void loop();
}



#endif