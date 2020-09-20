#ifndef TRANSITION_COMMAND_H
#define TRANSITION_COMMAND_H

#include "../command.h"

class Transition : public Command
{
public:
	Transition() { };
	Transition(float transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		amount = transition_amount;
	}
	~Transition() { };
	COMMAND_ID get_unique_id() { return COMMAND_ID::TRANSITION; };
	double get_amount(double elapsed_time)
	{
		double step_amount = amount * elapsed_time;
		time_to_complete -= elapsed_time;
		amount -= step_amount;
		return step_amount;
	}


private:
	float amount = 0.0;
};
#endif // !TRANSITION_COMMAND_H