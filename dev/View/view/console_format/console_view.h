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

class Console_View : public View
{
public:
	struct Console_State
	{
		enum
		{
			INPUT = 0,
			OUTPUT = 1
		};
		int current_state = OUTPUT;
	};
	Console_State state;
private:
};

#endif