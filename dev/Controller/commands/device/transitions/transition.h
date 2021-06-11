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
	Transition(Channel transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		total_elapsed_time = transition_time;
		amount = transition_amount / 100;
	};
	Transition(Channel transition_amount)
	{
		time_to_complete = 0;
		total_elapsed_time = 0;
		amount = transition_amount / 100;
	};
	~Transition() { };
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::TRANSITION; }
	/**
	 * \brief Calculation to move the position of a Device_State. 
	 * 
	 * Immediately move to the desired state.
	 * 
	 * \param position current device position.
	 * \param elapsed_time time since transition started.
	 */
	virtual void transition(Channel& position, double elapsed_time)
	{
		position = amount;
	}
	/**
	 * Change values in Device_State to reflect command.<br>
     * If device is not initalized, set state to invalid and return.<br>
     * Transitions amount of command by a percentage. Children classes should not implement this function. They should instead implement \ref transition(float&, double) "transition(position, elapsed_time)".
     * \param state reference to the state about to get mangled.
	 */
    virtual void mangle_state(Device_State& state) final
    {
		Channel_State c_state = static_cast<Channel_State&>(state);
        if(state.initalized == false)
        {
            c_state.valid = false;
            return;
        }
		c_state.power = true;
		if (c_state.get_position() != amount)
		{
			c_state.transitioning = true;
		}
		else
		{
			c_state.transitioning = false;
		}
		transition(c_state.get_position_ptr());

    }

protected:
	/**
	 Percentage of change.
	 */
	Channel amount = 0;
	/**
	 Current percentage of range.
	 */
	float current_position = -1;
	/**
	 How long this transition will take.
	 */
	double total_elapsed_time = 0.0;
private:
	void transition(Channel& position)
	{
		transition(position, total_elapsed_time - time_to_complete);
	}
};
#endif // !TRANSITION_COMMAND_H