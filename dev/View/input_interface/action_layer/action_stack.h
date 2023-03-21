/*****************************************************************//**
 * \file   action_stack.h
 * \brief
 *
 * \author kason
 * \date   November 2022
 *********************************************************************/
#ifndef KEYBOARD_ACTION_STACK_H
#define KEYBOARD_ACTION_STACK_H

#include <vector>

#include "action_layer.h"

/** List of action layers. */
class Action_Stack
{
public:
	Action_Stack();
	~Action_Stack();
	/**
	* \return Current active layer
	*/
	Action_Layer* get_active_layer();

	/**
	 * Add action layer to the stack.
	 * \return Index of the layer.
	 */
	int add_action_layer();

	/**
	 * Change which layer is active. 
	 * \param layer Index of layer to switch to.
	 */
	void change_action_layers(int layer);

	/**
	 * Setup the default action layers. Defaults to the layer of index 0.
	 */
	void setup_action_layers();


private:
	/**List of layers of actions that the keyboard can run*/
	std::map<int, Action_Layer> layers;
	/**List to current action layer*/
	Action_Layer* active_layer;

	int last_id;
};

#endif