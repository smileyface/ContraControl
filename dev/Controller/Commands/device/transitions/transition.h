/*****************************************************************//**
 * \file   transition.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/
#ifndef TRANSITION_COMMAND_H
#define TRANSITION_COMMAND_H

#include "../../command.h"
#include "../../../../Model/system/timer.h"

/**
*A command to transition the position of the device.
 */
class Transition : public Command
{
public:
	Transition() {};

	/**
	 * Constructor that gives an amount and a length of time for this transition to occur. For example, tranistion -20% over 200 ms.
	 * \param transition_amount Percentage to either add or remove from state. For addition, make it a positive amount. For subtraction, make it a negative amount.
	 * \param transition_time Length of time that the transition should take place.
	 * \todo change transition_amount from int to float
	 */
	Transition(int transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		amount = transition_amount / 100.0f;
	};
	~Transition() { };
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::TRANSITION; }
	/**
	 * Calculation to move the position of a Device_State  
	 */
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

	/**
	 * Change values in Device_State to reflect command.<br>
     * If device is not initalized, set state to invalid and return.<br>
     * Transitions amount of command by a percentage. Children classes should not implement this function. They should instead implement \ref set_device_position(float&, double) "set_device_position(position, elapsed_time)".
	 */
    virtual void mangle_state(Device_State& state) final
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