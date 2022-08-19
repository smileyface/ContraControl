/*****************************************************************//**
 * \file   keyboard_interface.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef INTERFACE_KEYBOARD_INTERFACE
#define INTERFACE_KEYBOARD_INTERFACE

class Keyboard_Interface
{
public:
	Keyboard_Interface();
	virtual ~Keyboard_Interface();
	void start_listening();

	virtual void readEv() = 0;
	short getKeyState(short key);
	bool get_keyboard_present();

protected:
private:
	bool active;
	bool keyboard_present;	
	void loop();

};

#endif
