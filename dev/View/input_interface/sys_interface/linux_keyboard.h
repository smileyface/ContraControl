#ifdef __linux__

#ifndef LINUX_KEYBOARD_H
#define LINUX_KEYBOARD_H

#include <iostream>
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>

#include "key_input_interface.h"
#include "keyboard_interface.h"

#define KEYBOARD_DEV "/dev/input/event0"

struct keyboard_state
{
	signed short keys[KEY_CNT];
};

class Linux_Keyboard : public Keyboard_Interface
{
public:
	Linux_Keyboard();
	~Linux_Keyboard();
	void readEv();
	short getKeyState(short key);
protected:
private:
	pthread_t thread;
	bool active;
	int keyboard_fd;
	input_event* keyboard_ev;
	keyboard_state* keyboard_st;
	char name[256];
	bool keyboard_present;

	void initalize_codes();
};

#endif

#endif // __linux__
