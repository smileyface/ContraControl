/*****************************************************************//**
 * \file   option_popup_response_message.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef MESSAGE_TYPE_OPTION_POPUP_RESPONSE_MESSAGE
#define MESSAGE_TYPE_OPTION_POPUP_RESPONSE_MESSAGE

#include "../response_message.h"
#include "../../view_messages/view_request/option_popup_message.h"

/** Message to respond to Option_Popup_Message with. Will contain the selected option. */
class Option_Popup_Response_Message : public Response_Message
{
public:
	Option_Popup_Response_Message();
	/**
	 * Constructor that sets the message
	 * 
	 * \param selection Index of the option that the user selected.
	 * \param responding_message Pointer to the message we're responding to.
	 */
	Option_Popup_Response_Message(int selection, Option_Popup_Message* responding_message);
	
	/** \return Selected option */
	int get_selection();

	/** Checks if we are responding to the correct message */
	virtual bool this_message(Option_Popup_Message* check_message);

private:
	int selection_;
	Option_Popup_Message* responding_message_;
};

#endif