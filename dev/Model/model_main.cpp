#include "model_main.h"

#include "types.h"
#include "../Interfaces/model_interface.h"
#include "../Controller/Commands/common/initalize.h"

Timer model_timer;

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

Device* model::get_device(Device_Name device_name)
{
	return known_devices[device_name];
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
	Model_Command m_command(device->get_id(), new Initalize(name));
	model_interfaces::controller_interface::request_command(m_command, 0);
}
void model::step()
{
	std::vector<int> completed_index = model::run_commands();

	for (size_t i = 0; i < completed_index.size(); i++) {
		model::step_actions.erase(step_actions.begin() + completed_index[i]);
	}
	model_timer.update_time();
}

void model::stop_loop()
{
	model_running = false;
}

void model::clean_up()
{
	model::known_devices.erase(model::known_devices.begin(), model::known_devices.end());
}

std::vector<int> model::run_commands()
{
	std::vector<int> completed_index;
	for (int i = 0; i < model::step_actions.size(); i++) {

			model::get_device(model::step_actions[i].id)->run_command(model::step_actions[i].command);
			model::system_commands(model::step_actions[i].command);
			if(model::step_actions[i].command->completed())
				completed_index.push_back(i);

	}
	return completed_index;
}

void model::system_commands(Command* commands)
{
	if (commands->get_id() == COMMAND_ENUM::INITALIZE)
	{
		model::id_map.clear();
		model::initalize();
	}
}
