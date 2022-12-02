/*****************************************************************//**
 * \file   action_layer.h
 * \brief
 *
 * \author kason
 * \date   November 2022
 *********************************************************************/
#ifndef KEYBOARD_ACTION_LAYER_H
#define KEYBOARD_ACTION_LAYER_H

#include "input_buffer.h"

/** A map to house key code to KPI translation data */
typedef std::map<int, KPI> Keyboard_Code_Map;
/** A callback function for keystroke events */
typedef std::function<void()> Keyboard_Event;

/** Map for holding system specific keycodes to a common code */
extern Keyboard_Code_Map master_code_map;

/** Buffer for the keyboard input. */
extern Keyboard_Input_Buffer input_buffer;
/**
 * Structure for storing on_press, on_hold, and on_release commands associated with a key stroke.
 */
class Action_Layer
{
public:
	Action_Layer();
	~Action_Layer();

	/**
	 * Set on_press to a user-defined callback
	 * \param key Key to assign callback function to
	 * \param function a callback
	 */
	void set_on_press(KPI key, Keyboard_Event function);

	/**
	* Set on_released to a user-defined callback
	* \param key Key to assign callback function to
	* \param function a callback
	*/
	void set_on_release(KPI key, Keyboard_Event function);

	/**
	* Set on_hold to a user-defined callback
	* \param key Key to assign callback function to
	* \param function a callback
	*/
	void set_on_hold(KPI key, Keyboard_Event function);

	/**
	 * Handle a change in key state
	 * \param key Key that state has changed for
	 * \param event_value Value of the state change caused by captured event
	 */
	void handle_event(KPI key, int event_value);

	/**
	 * Special commands when transitioning to this layer.
	 */
	void transition_to();

	/**
	 * Special commands when transitioning away from this layer.
	 */
	void transition_from();

private:
	Keyboard_Code_Map code_map;
	
	
};

#endif