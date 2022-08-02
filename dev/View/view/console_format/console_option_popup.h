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
#include "../view_type/option_view_type.h"

/** A popup on the console for getting feedback from users */
class Console_Option_Popup : public Console_View
{
public:
	void on_display();
	void on_refresh();
	void on_paint();
	void on_input();
	/**
	 * Set options for the popup.
	 * 
	 * \param list List of options.
	 */
	void set_options(std::vector<std::string> list);
	/**
	 * \return the selected option.
	 */
	int get_option();

	bool is_stale();
private:
	int choice = -1;
	std::vector<std::string> options;
};
#endif
