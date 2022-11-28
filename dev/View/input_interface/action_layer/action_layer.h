/*****************************************************************//**
 * \file   action_layer.h
 * \brief
 *
 * \author kason
 * \date   November 2022
 *********************************************************************/
#ifndef KEYBOARD_ACTION_LAYER_H
#define KEYBOARD_ACTION_LAYER_H

#include "../sys_interface/key_input_interface.h"

typedef std::map<int, KPI> Keyboard_Code_Map;
typedef std::function<void()> Keyboard_Event;

/** Map for holding system specific keycodes to a common code */
extern Keyboard_Code_Map master_code_map;

class Action_Layer
{
public:
	Action_Layer();
	~Action_Layer();
	/**
	* \return Map of system defined code to common defined code
	*/
	Keyboard_Code_Map get_codemap();

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

	void set_on_hold(KPI key, Keyboard_Event function);

	void add_code(int code, KPI key);

	void handle_event(int code, int event_value);

	void transition_to();

	void transition_from();


private:
	Keyboard_Code_Map code_map;

	
};

#endif