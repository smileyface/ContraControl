#ifndef SAVE_READER_H
#define SAVE_READER_H


#include "../Interfaces/model_interface.h"
#include "../Interfaces/controller_interface.h"

namespace file_reader {
	std::function<void()>read_devices = []() {
	};
	std::function<void()>read_commands = []() {
	};

	std::function<void()>read_file = []() {
		file_reader::read_devices();
		file_reader::read_commands();
	};


}
#endif // !SAVE_READER_H
