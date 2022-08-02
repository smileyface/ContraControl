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

/** List of options for the view to display */
typedef std::vector<std::string> Option_List;

/**
 * A request for the View subsystem to create an option popup. Give the users a list of options and get feedback.
 */
class Option_Popup_Message : public View_Subsystem_Message
{
public:
	Option_Popup_Message();
	/**
	 * Constructor.
	 * \param from Subsystem sending the message. This is so we know who to send return messages to.
	 * \param list_of_options Options to request from the view.
	 */
	Option_Popup_Message(SUBSYSTEM_ID_ENUM from, Option_List list_of_options);
	/**
	 * \return List of options to request from the view.
	 */
	Option_List get_options();
	void placeholder();
private:
	Option_List options;
};
