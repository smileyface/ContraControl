/*****************************************************************//**
 * \file   linear_transition.h
 * \brief  
 * 
 * \author kason
 * \date   April 2021
 *********************************************************************/

#ifndef LINEAR_TRANSITIONS_COMMAND_H
#define LINEAR_TRANSITIONS_COMMAND_H

#include <cmath>

#include "transition.h"

/*!
 *  A command that transitions the position in a device in a linear manner over time.
 */
class Linear_Transition : public Transition
{
public:
	Linear_Transition() {};
	/**
	* Constructor that gives an desired_value and a length of time for this transition to occur. For example, tranistion -20% over 200 ms.
	* \param transition_amount Percentage to either add or remove from state. For addition, make it a positive desired_value. For subtraction, make it a negative desired_value.
    * \param transition_time Length of time that the transition should take place.
    * \todo change transition_amount from int to float
    */
	Linear_Transition(Channel transition_amount, double transition_time)
	{
		time_to_complete = transition_time;
		desired_value = transition_amount / 100;
	}
	/**
 * \brief Calculation to move the position of a Device_State.
 *
 * Transition in a linear manner with position over time.
 *
 * \param position current device position.
 * \param elapsed_time time since transition started.
 * \return This shouldn't return a thing, but Doxy thinks it does.
 */
	virtual void transition(Channel position, double elapsed_time)
	{
		position = (int)round(((desired_value / time_to_complete) * elapsed_time) + (position / desired_value));
	}
};
#endif // !LINEAR_TRANSITIONS_COMMAND_H
