/*******************************************************************//**
 * \file   console_option_popup.h
 * \brief
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/

#ifndef CONSOLE_OPTION_POPUP_VIEW
#define CONSOLE_OPTION_POPUP_VIEW

#include <vector>

#include "console_view.h"

class Console_Option_Popup : public Console_View
{
public:
	void on_display();
	void on_refresh();
	void on_paint();
	void on_input();
	void set_options(std::vector<std::string> list);
	int get_option();

private:
	int choice = -1;
	std::vector<std::string> options;
};
#endif
