/*****************************************************************//**
 * \file   windows_keyboard.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/
#ifdef _WIN32

#ifndef WINDOWS_KEYBOARD_H
#define WINDOWS_KEYBOARD_H

#include "keyboard_interface.h"

/** Keyboard interface for windows */
class Windows_Keyboard : public Keyboard_Interface
{
public:
	Windows_Keyboard();
	~Windows_Keyboard();
	bool connect_to_keyboard();
	void initalize_codes();

	void readEv();

protected:
private:
	bool keyboard_present;

};



#endif
#endif
