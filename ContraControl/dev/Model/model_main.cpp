#include "model_main.h"

Timer model::timer;
std::map<Device_Name, Device*> model::known_devices;
bool model::model_running = true;

std::vector<model::Model_Command> model::step_run;
std::map<Device_Id, Device_Name> model::id_map;

void model::initalize()
{
	std::map<Device_Name, Device*>::iterator it;
	for (it = known_devices.begin(); it != known_devices.end(); it++) {
		id_map[it->second->get_id()] = it->first;
	}

}
void model::add_to_step(Model_Command theCommand)
{
	model::step_run.emplace_back(theCommand);
}
void model::add_device(std::string name, Device* device)
{
	model::known_devices.emplace(name, device);
}
void model::loop()
{
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
	for (int i = completed_index.size() - 1; i > -1; i--) {
		model::step_run.erase(step_run.begin() + completed_index[i]);
	}
	timer.update_time();

	//}
}

void model::stop_loop()
{
	model_running = false;
}

model::Model_Command::Model_Command(Device_Id id, Command* command)
{
	this->command = command;
	this->id = id;
}
