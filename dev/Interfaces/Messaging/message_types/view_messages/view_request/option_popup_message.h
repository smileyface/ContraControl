/*******************************************************************//**
 * \file   option_popup_message.h
 * \brief
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/

#include "../view_subsystem_message.h"

class Option_Popup_Message : public View_Subsystem_Message
{
public:
	void placeholder();
private:
	std::vector<std::string> options;
};
