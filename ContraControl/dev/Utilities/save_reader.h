#ifndef SAVE_READER_H
#define SAVE_READER_H


#include "../Model/model_main.h"
#include "../Controller/controller_main.h"

namespace file_reader {
	std::function<void()>read_devices = []() {
		model::known_devices["Device_1"] = new SwitchDevice();
		model::known_devices["Device_2"] = new SwitchDevice();
	};
	std::function<void()>read_commands = []() {
		controller::test_commands.push_back(std::make_pair(100, std::make_pair(model::known_devices["Device_1"]->get_id(), On())));
		controller::test_commands.push_back(std::make_pair(200, std::make_pair(model::known_devices["Device_1"]->get_id(), Off())));
	};

	std::function<void()>read_file = []() {
		file_reader::read_devices();
		file_reader::read_commands();
	};


}
#endif // !SAVE_READER_H
