#include "model_main.h"

#include "interfaces/types.h"
#include "interfaces/controller.h"
#include "interfaces/model_actions.h"

Timer model::timer;
std::map<Device_Name, Device*> model::known_devices;
bool model::model_running = true;

std::vector<Model_Command> model::step_actions;
std::map<Device_Id, Device_Name> model::id_map;

Device* model::get_device(Device_Id device_id)
{
	if (known_devices[id_map[device_id]] == nullptr)
	{
		Logger::getInstance()->addItem(LOG_PRIORITY::ERROR, "Invalid Device Id Called", "INVALID");
		throw - 1;
	}
	return known_devices[id_map[device_id]];
}

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
	Model_Command m_command(device->get_id(), model_interfaces::controller_interface::get_command_object(COMMAND_ID::INITALIZE, name));
	model_interfaces::controller_interface::request_command(m_command, 0);
}
void model::step()
{
	//while (model_running) {
	std::vector<int> completed_index;
	for (int i = 0; i < step_actions.size(); i++) {
		if (step_actions[i].command->time_to_complete <= 0) {
			model_action::run_command(step_actions[i].command, *model::get_device(step_actions[i].id));
			completed_index.push_back(i);
		}
		else {
			step_actions[i].command->time_to_complete -= model::timer.elapsed_time;
		}
	}
	for (size_t i = 0; i < completed_index.size(); i++) {
		model::step_actions.erase(step_actions.begin() + completed_index[i]);
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
