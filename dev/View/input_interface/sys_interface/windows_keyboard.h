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




class Windows_Keyboard : public Keyboard_Interface
{
public:
	Windows_Keyboard();
	~Windows_Keyboard();
	void readEv();
	short getKeyState(short key);

protected:
private:
	bool keyboard_present;

	void initalize_codes();
};



#endif
#endif