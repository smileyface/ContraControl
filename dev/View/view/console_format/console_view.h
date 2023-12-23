 /*****************************************************************//**
 * \file   console_view.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW_CONSOLE_VIEW_H
#define VIEW_CONSOLE_VIEW_H

#include "../view.h"
#include "../../input_interface/sys_interface/keyboard_interface.h"

/** A view to display on the console. */
class Console_View : public View
{
public:
	Console_View();
	virtual ~Console_View();

	virtual void on_create();
	virtual void on_destroy();

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
	Keyboard_Interface* keyboard = 0;
private:
};

#endif