#ifndef TRANSITION_COMMAND_H
#define TRANSITION_COMMAND_H

#include "../../command.h"
#include "../../../../Model/system/timer.h"

class Transition : public Command
{
public:
	Transition() {};
	Transition(int transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		amount = transition_amount / 100.0f;
	};
	~Transition() { };
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::TRANSITION; }
	virtual void set_device_position(float& position, double elapsed_time)
	{
		position = amount;

	}
	void transition(float& position, double elapsed_time)
	{
		total_elapsed_time += elapsed_time;
		set_device_position(position, elapsed_time);
		time_to_complete -= elapsed_time;
	}
	std::string get_unique_id() 
	{
		return "TRANSITION: T=" + std::to_string(time_to_complete + total_elapsed_time) + " P=" + std::to_string(amount);
	}
    virtual void mangle_state(Device_State& state)
    {
        if(state.initalized == false)
        {
            state.valid = false;
            return;
        }
		state.power = true;
		if (state.position != amount)
		{
			state.transitioning = true;
		}
		else
		{
			state.transitioning = false;
		}
        transition(state.position, model_timer.get_elapsed_time());
    }

protected:
	float amount = 0.0;
	float current_position = -1;
	double total_elapsed_time = 0.0;
};
#endif // !TRANSITION_COMMAND_H