#include "controller_main.h"

Timer controller::controller_timer;
bool controller::controller_running = true;
std::vector<Timed_Command> controller::test_commands;

bool controller::sort_pair(Timed_Command i, Timed_Command j)
{
		return i.time < j.time;
}

void controller::initalize()
{
	std::map<std::string, Device*>::iterator it;
	for (it = model::known_devices.begin(); it != model::known_devices.end(); it++) {
		test_commands.emplace_back(Timed_Command(new Initalize(), it->second->get_id(), 0));
	}
	std::sort(test_commands.begin(), test_commands.end(), sort_pair);
	controller_timer.reset_clock();
}

void controller::stop_controller()
{
	controller_running = false;
}

void controller::loop()
{
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
	for (int i = remove_indexes.size() - 1; i > -1; i--) {
		test_commands.erase(test_commands.begin() + remove_indexes[i]);
	}
	controller_timer.update_time();

	//}
}
