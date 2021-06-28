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
#include "Interfaces/types/channel.h"

/**
*A command to transition the position of the device.
 */
class Transition : public Command
{
public:
	Transition() {};

	/**
	 * Constructor that gives the desired channel value and a length of time for this transition to occur.
	 * \param desired_value The final channel value.
	 * \param transition_time Length of time that the transition should take place.
	 */
	Transition(Channel desired_value, double transition_time)
	{
		time_to_complete = transition_time;
		total_elapsed_time = 0;
		desired_value = desired_value;
	};
	/**
	 * Constructor that gives a desired_value and expects to do it immediately.
	 * \param desired_value The final channel value.
	 */
	Transition(Channel desired_value)
	{
		time_to_complete = 0;
		total_elapsed_time = 0;
		desired_value = desired_value;
	};
	~Transition() { };
	virtual COMMAND_ENUM get_id() { return COMMAND_ENUM::TRANSITION; }

	
	/**
	 * \brief Calculation to move the position of a Device_State.
	 *
	 * Move the channel based on the equation in transition(Channel& position, double elapsed_time).
	 *
	 * \param position pointer to the current channels position.
	 */
	void transition(Channel& position);
protected:
	/**
 * \brief Calculation to move the position of a Device_State.
 *
 * Immediately move to the desired state.
 *
 * \param position pointer to the current channels position.
 * \param elapsed_time time since transition started.
 */
	virtual void transition(Channel& position, double elapsed_time)
	{
		position = desired_value;
	}
	/**
	 Percentage of change.
	 */
	Channel desired_value = 0;
	/**
	 Current percentage of range.
	 */
	Channel current_position = 0;
	/**
	 How long this transition will take.
	 */
	double total_elapsed_time = 0.0;

};
#endif // !TRANSITION_COMMAND_H