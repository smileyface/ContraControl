#include "model_main.h"

#include "interfaces/types.h"
#include "interfaces/controller.h"

Timer model::timer;
std::map<Device_Name, Device*> model::known_devices;
bool model::model_running = true;

std::vector<Model_Command> model::step_run;
std::map<Device_Id, Device_Name> model::id_map;

void model::initalize()
{
	std::map<Device_Name, Device*>::iterator it;
	for (it = known_devices.begin(); it != known_devices.end(); it++) {
		id_map[it->second->get_id()] = it->first;
	}

}
void model::add_device(std::string name, Device* device)
{
	model::known_devices.emplace(name, device);
	Model_Command m_command(device->get_id(), model_interfaces::controller_interface::get_command_object(COMMAND_ID::INITALIZE));
	model_interfaces::controller_interface::request_command(m_command, 0);
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

void model::clean_up()
{
	model::known_devices.erase(model::known_devices.begin(), model::known_devices.end());
}
