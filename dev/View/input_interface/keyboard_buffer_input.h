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


class Keyboard_Buffer_Input
{
public:
	Keyboard_Buffer_Input();
	std::string get_input();
	int get_number();
	Keyboard_Interface* keyboard;
private:
	bool block;
	std::vector<char> buffer;
};
#endif
