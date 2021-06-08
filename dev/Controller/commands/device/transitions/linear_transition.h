/*****************************************************************//**
 * \file   linear_transition.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef LINEAR_TRANSITIONS_COMMAND_H
#define LINEAR_TRANSITIONS_COMMAND_H

#include "transition.h"

/*!
 *  A command that transitions the position in a device in a linear manner over time.
 */
class Linear_Transition : public Transition
{
public:
	Linear_Transition() {};
	/**
	* Constructor that gives an amount and a length of time for this transition to occur. For example, tranistion -20% over 200 ms.
	* \param transition_amount Percentage to either add or remove from state. For addition, make it a positive amount. For subtraction, make it a negative amount.
    * \param transition_time Length of time that the transition should take place.
    * \todo change transition_amount from int to float
    */
	Linear_Transition(int transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		amount = transition_amount / 100.0f;
	}
	/**
 * \brief Calculation to move the position of a Device_State.
 *
 * Transition in a linear manner with position over time.
 *
 * \param position current device position.
 * \param elapsed_time time since transition started.
 */
	virtual void transition(double& position, double elapsed_time)
	{
		position = ((amount / time_to_complete) * elapsed_time) + (position / amount);
	}
};
#endif // !LINEAR_TRANSITIONS_COMMAND_H
