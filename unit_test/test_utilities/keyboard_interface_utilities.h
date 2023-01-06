#ifndef KEYBOARD_INTERFACE_UTILITIES
#define KEYBOARD_INTERFACE_UTILITIES

#include "../../dev/View/input_interface/sys_interface/keyboard_interface.h"

class Test_Keyboard_Interface : public Keyboard_Interface
{
public:
	Test_Keyboard_Interface();
	void initalize_codes();
	void connect_to_keyboard();
	void readEv();

	bool read_a_character;
};

#endif