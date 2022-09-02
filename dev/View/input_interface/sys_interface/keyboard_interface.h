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
#include <string>

class Keyboard_Interface
{
public:
	Keyboard_Interface();
	virtual ~Keyboard_Interface();

	virtual void initalize_codes() = 0;

	virtual bool connect_to_keyboard(std::string path_to_keyboard) = 0;

	void start_listening();
	void stop_listening();

	virtual void readEv() = 0;
	bool get_keyboard_present();
	void set_on_press(KPI key, std::function<void()> function);

protected:
	std::map<int, KPI> code_map;
	bool active;
	bool keyboard_present;
private:
	void loop();


};

#endif
