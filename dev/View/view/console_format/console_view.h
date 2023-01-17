/*****************************************************************//**
 * \file   console_view.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW_CONSOLE_VIEW_H
#define VIEW_CONSOLE_VIEW_H

#include <string>
#include "../view.h"
#include "../../input_interface/keyboard_buffer_input.h"

/** A view to display on the console. */
class Console_View : public View
{
public:
	Console_View();
	/** Console is unique, because the window that the out goes is the same that the in comes in. */
	struct Console_State
	{
		enum
		{
			/** Console is waiting for user input. */
			INPUT = 0,
			/** Console is displaying. */
			OUTPUT = 1
		};
		/** Are we in or out state. */
		int current_state = OUTPUT;
	};
	/** Access to the input/output state of the console */
	Console_State state;

protected:
	/** Message to "paint" (display) into the console. As the console is acsii only, this is a string */
	std::string painted_message;
	/** The console interface to an input device. Namely the Keyboard */
	Keyboard_Buffer_Input keyboard;
private:
};

#endif