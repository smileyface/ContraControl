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
#include "../Controller/system/timer.h"
typedef unsigned char Channel;
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
		total_elapsed_time = 0;
		amount = transition_amount;
	};
	Transition(Channel transition_amount)
	{
		time_to_complete = 0;
		total_elapsed_time = 0;
		amount = transition_amount;
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
	
	void transition(Channel& position)
	{
		transition(position, total_elapsed_time - time_to_complete);
		current_position = position;
		total_elapsed_time += controller_timer.elapsed_time;
	}
protected:
	/**
	 Percentage of change.
	 */
	Channel amount = 0;
	/**
	 Current percentage of range.
	 */
	Channel current_position = -1;
	/**
	 How long this transition will take.
	 */
	double total_elapsed_time = 0.0;

};
#endif // !TRANSITION_COMMAND_H