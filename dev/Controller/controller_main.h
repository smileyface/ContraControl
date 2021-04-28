
#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include <vector>
#include <algorithm>
#include <functional>

#include "../Utilities/timer.h"
#include "../Interfaces/types/timed_command.h"



namespace controller
{
	extern Timer controller_timer;
	extern bool controller_running;
	extern std::vector<Timed_Command> controller_queue;

	bool sort_pair(Timed_Command i, Timed_Command j);

	void initalize();
	void stop_controller();
	void add_command(Timed_Command tc);

	void step();

	void clean_up();
}



#endif