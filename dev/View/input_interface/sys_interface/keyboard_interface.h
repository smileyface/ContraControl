/*****************************************************************//**
 * \file   keyboard_interface.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef INTERFACE_KEYBOARD_INTERFACE
#define INTERFACE_KEYBOARD_INTERFACE

#include "../action_layer/action_stack.h"

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
	virtual void connect_to_keyboard() = 0;

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
	* Stack of action layers for keyboard interaction.
	 */
	Action_Stack action_stack;

	/**
	* Get a simple line of text from the keyboard. This is a blocking call.
	 * \return Simple line of text.
	 */
	std::string get_simple();
protected:
	/** Is the interface active.  */
	bool active;
	/** Is there a physical or virtual keyboard present on the system*/
	bool keyboard_present;
private:
	void loop();
	


};

#endif
