/*****************************************************************//**
 * \file   option_view_type.h
 * \brief
 *
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef VIEW_OPTION_VIEW_TYPE
#define VIEW_OPTION_VIEW_TYPE

#include "Messaging/consumers.h"

 /** A UI type for nandling options*/
class Option_View_Type
{
public:
	Option_View_Type();
	/**The log message captured from the message relay.*/
	struct MESSAGE
	{
		std::string QUERY; ///<Message to display to the user
		std::vector<std::string> OPTIONS;///<Log message.
	} message;///<Instance of the captured message.
	/**Get the log message from the message relay.*/
	void get_message();

protected:
	/**
	* .Message Consumer
	*/
	Message_Consumer* option_consumer;
	/**
	 * Message recieved.
	 */
	Option_Popup_Message* specified_message;
};
#endif // !VIEW_OPTION_VIEW_TYPE
