/*****************************************************************//**
 * \file   keyboard_buffer_input.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/
#ifndef INPUT_INTERFACE_KEYBOARD
#define INPUT_INTERFACE_KEYBOARD

#include <vector>
#include <string>

#include "sys_interface/keyboard_interface.h"

/** This is an interface for keyboard input */
class Keyboard_Buffer_Input
{
public:
	Keyboard_Buffer_Input();
	/**
	* Get string of characters recived from the keyboard. Terminated with an ENTER key press.
	* \return entered string. 
	*/
	std::string get_input();
	/**
	 * Get number entered from the keyboard. Terminated with an ENTER key press.
	 * \return number entered.
	 */
	int get_number();
	/**
	 * Appropriate keyboard for the system.
	 * 
	 * \see Linux_Keyboard
	 * \see Windows_Keyboard
	 */
	Keyboard_Interface* keyboard;
private:
	bool block;
	std::vector<char> buffer;
};
#endif
