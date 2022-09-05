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

/** Generic interface for reading keypresses from a keyboard. */
class Keyboard_Interface
{
public:
	Keyboard_Interface();
	virtual ~Keyboard_Interface();

	/**
	 * Setup the codemap.
	 */
	virtual void initalize_codes() = 0;

	/**
	 * Connect to the physical or vitrual keyboard.
	 * 
	 * \return whether connection is successful 
	 */
	virtual bool connect_to_keyboard() = 0;

	/**
	 * Start listening for input from the modeled keyboard 
	 */
	void start_listening();
	/**
	 * Stop listening for input from the modeled keyboard.
	 */
	void stop_listening();

	/**
	 * Read an event from the keyboard
	 */
	virtual void readEv() = 0;
	
	/**
	 * \return Is there a physical or virtual keyboard present.
	 */
	bool get_keyboard_present();

	/**
	 * Set on_press to a user-defined callback
	 * \param key Key to assign callback function to
	 * \param function a callback
	 */
	void set_on_press(KPI key, std::function<void()> function);

protected:
	/** Map for holding system specific keycodes to a common code */
	std::map<int, KPI> code_map;
	/** Is the interface active.  */
	bool active;
	/** Is there a physical or virtual keyboard present on the system*/
	bool keyboard_present;
private:
	void loop();


};

#endif
