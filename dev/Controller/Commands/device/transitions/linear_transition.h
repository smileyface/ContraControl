#ifndef LINEAR_TRANSITIONS_COMMAND_H
#define LINEAR_TRANSITIONS_COMMAND_H

#include "transition.h"

class Linear_Transition : public Transition
{
public:
	Linear_Transition() {};
	Linear_Transition(int transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		amount = transition_amount / 100.0f;
	}
	virtual void set_device_position(double& position, double elapsed_time)
	{
		position = ((amount / time_to_complete) * elapsed_time) + (position / amount);
	}
};
#endif // !LINEAR_TRANSITIONS_COMMAND_H
