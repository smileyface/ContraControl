/*******************************************************************//**
 * \file   option_popup_message.h
 * \brief
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/

#include <vector>
#include <string>

#include "../view_subsystem_message.h"

typedef std::vector<std::string> Option_List;

class Option_Popup_Message : public View_Subsystem_Message
{
public:
	Option_Popup_Message();
	Option_Popup_Message(SUBSYSTEM_ID_ENUM from, Option_List list_of_options);
	Option_List get_options();
	void placeholder();
private:
	Option_List options;
};
