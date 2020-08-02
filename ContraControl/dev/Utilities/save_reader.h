#ifndef SAVE_READER_H
#define SAVE_READER_H


#include "../Model/model_main.h"
#include "../Controller/controller_main.h"

namespace file_reader {
	std::function<void()>read_devices = []() {
		model::known_devices["Device_1"] = new SwitchDevice("Device_1");
		model::known_devices["Device_2"] = new SwitchDevice("Device_2");
	};
	std::function<void()>read_commands = []() {
		controller::test_commands.push_back(Timed_Command(new On(), "Device_1", 100));
		controller::test_commands.push_back(Timed_Command(new Off(), "Device_1", 200));
	};

	std::function<void()>read_file = []() {
		file_reader::read_devices();
		file_reader::read_commands();
	};


}
#endif // !SAVE_READER_H
