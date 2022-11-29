/*******************************************************************//**
 * \file   option_popup_message.h
 * \brief
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/
#ifndef MESSAGE_TYPE_OPTION_POPUP_MESSAGE
#define MESSAGE_TYPE_OPTION_POPUP_MESSAGE
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
	 * \param option_query Message to query the user.
	 * \param list_of_options Options to request from the view.
	 */
	Option_Popup_Message(SUBSYSTEM_ID_ENUM from, std::string option_query, Option_List list_of_options);
	/**
	 * \return List of options to request from the view.
	 */
	Option_List get_options();
	/**
	 * \return Query message to display to the user,
	 */
	std::string get_option_query();

	void placeholder();
private:
	Option_List options_;
	std::string option_query_;
};

#endif