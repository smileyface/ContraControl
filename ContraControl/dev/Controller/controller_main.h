
#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include <vector>
#include <functional>

typedef  std::function<void()> func_ptr;

enum TIMES : uint16_t
{
	NOW = 0
};



namespace controller
{
	bool controller_running = true;
	typedef  std::pair<int, func_ptr> timed_command;
	std::vector<timed_command> commands;

	func_ptr initalize = []() {

	};

	func_ptr stop_controller = []() {
		controller_running = false;
	};

	func_ptr loop = []() {
		while (controller_running) {

		}
	};

}



#endif