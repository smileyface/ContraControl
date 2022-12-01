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
class Keyboard_Input_Buffer
{
public:
	Keyboard_Input_Buffer();
	~Keyboard_Input_Buffer();

	void add(KPI key, KEY_STATE state);
	std::string get_buffer();
	void clear();
private:
	std::vector<std::pair<KPI, KEY_STATE>> input_buffer;
};
#endif