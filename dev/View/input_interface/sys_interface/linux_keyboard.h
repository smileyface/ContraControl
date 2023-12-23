/*****************************************************************//**
 * \file   linux_keyboard.h
 * \brief  
 * 
 * \author kason
 * \date   September 2022
 *********************************************************************/

#ifdef __linux__

#ifndef LINUX_KEYBOARD_H
#define LINUX_KEYBOARD_H

#include <iostream>
#include <fcntl.h>
#include <linux/input.h>

#include "keyboard_interface.h"


struct keyboard_state
{
	signed short keys[KEY_CNT];
};

class Linux_Keyboard : public Keyboard_Interface
{
public:
	Linux_Keyboard();
	~Linux_Keyboard();
	void connect_to_keyboard();
	void readEv();
	short getKeyState(short key);

	void initalize_codes();

protected:

	void connect_to_keyboard(std::string path_to_keyboard);
private:
	pthread_t thread;
	int keyboard_fd;
	input_event* keyboard_ev;
	keyboard_state* keyboard_st;
	char name[256];

};

#endif

#endif // __linux__
