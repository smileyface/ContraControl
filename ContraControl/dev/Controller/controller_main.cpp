#include "controller_main.h"


#include "../Model/interfaces/types.h"
#include "Interfaces/model.h"

Timer controller::controller_timer;
bool controller::controller_running = true;
std::vector<Timed_Command> controller::controller_queue;

bool controller::sort_pair(Timed_Command i, Timed_Command j)
{
		return i.time < j.time;
}

void controller::initalize()
{
	controller_timer.reset_clock();
}

void controller::stop_controller()
{
	controller_running = false;
}

void controller::step()
{
	//while (controller_running) {
	double time = controller_timer.get_elapsed_time();
	std::vector<int> remove_indexes;
	for (int i = 0; i < controller_queue.size(); i++) {
		if (controller_queue[i].time <= 0)
		{
			controller_interfaces::model_interface::send_command(controller_queue[i]);
			remove_indexes.push_back(i);
		}
		else {
			controller_queue[i].time -= time;
		}
	}
	for (int i = remove_indexes.size() - 1; i > -1; i--) {
		controller_queue.erase(controller_queue.begin() + remove_indexes[i]);
	}
	controller_timer.update_time();

	//}
}

void controller::clean_up()
{
}
