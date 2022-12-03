/*****************************************************************//**
 * \file   input_buffer.h
 * \brief  
 * 
 * \author kason
 * \date   November 2022
 *********************************************************************/
#ifndef KEYBOARD_INPUT_BUFFER_H
#define KEYBOARD_INPUT_BUFFER_H

#include <vector>
#include <string>

#include "../sys_interface/key_input_interface.h"

/**
 * A buffer for capturing input from the keyboard.
 */
class Keyboard_Input_Buffer
{
public:
	Keyboard_Input_Buffer();
	~Keyboard_Input_Buffer();

	/**
	 * Add a key state change to the buffer.
	 * \param key The key that has had a state change.
	 * \param state State of the action of the key
	 */
	void add(KPI key, KEY_STATE state);
	/**
	 * Get the buffer decoded to a string.
	 * \return The decoded buffer.
	 */
	std::string get_buffer();
	/**
	 * Clear the buffer.
	 */
	void clear();

private:
	/** Buffer containter */
	std::vector<std::pair<KPI, KEY_STATE>> input_buffer;
};
#endif