/*****************************************************************//**
 * \file   action_stack.h
 * \brief
 *
 * \author kason
 * \date   November 2022
 *********************************************************************/
#ifndef KEYBOARD_ACTION_STACK_H
#define KEYBOARD_ACTION_STACK_H

#include <functional>
#include <vector>

#include "action_layer.h"

class Action_Stack
{
public:
	Action_Stack();
	/**
	* \return Current active layer
	*/
	Action_Layer* get_active_layer();

	int add_action_layer();

	void change_action_layers(int layer);

	void setup_action_layers();
private:
	/**List of layers of actions that the keyboard can run*/
	std::vector<Action_Layer> layers;
	/**List to current action layer*/
	Action_Layer* active_layer = 0;
};

#endif