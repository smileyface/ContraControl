#include "device/transitions/transition.h"

#include "../system/timer.h"

void Transition::transition(Channel& position)
{
	current_position = position;
	transition(position, total_elapsed_time - time_to_complete);
	total_elapsed_time += controller_timer.get_elapsed_time();
}
