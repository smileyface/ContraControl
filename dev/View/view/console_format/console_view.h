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

/** A view to display on the console. */
class Console_View : public View
{
public:
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
	std::string painted_message;
private:
};

#endif