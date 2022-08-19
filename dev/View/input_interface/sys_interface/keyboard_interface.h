/*****************************************************************//**
 * \file   keyboard_interface.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef INTERFACE_KEYBOARD_INTERFACE
#define INTERFACE_KEYBOARD_INTERFACE

#include "key_input_interface.h"

class Keyboard_Interface
{
public:
	Keyboard_Interface();
	virtual ~Keyboard_Interface();
	void start_listening();

	virtual void readEv() = 0;
	bool get_keyboard_present();
	void set_on_press(KPI key, std::function<void()> function);

protected:
	std::map<int, KPI> code_map;
private:
	bool active;
	bool keyboard_present;	
	void loop();
	virtual void initalize_codes() = 0;


};

#endif
