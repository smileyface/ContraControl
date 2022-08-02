/*******************************************************************//**
 * \file   internal_messages.h
 * \brief  List of Internal Messages
 *
 * \author kason
 * \date   June 2022
 *********************************************************************/

#ifndef INTERNAL_MESSAGES_LIST
#define INTERNAL_MESSAGES_LIST

 //#include "internal_message_type.h"
#include "message_types/logging_message.h"
//#include "message_types/view_messages/view_subsystem_message.h"
#include "message_types/view_messages/view_request/option_popup_message.h"

/**
 * Types of Internal_Messages for consumers to use
 */
struct Message_Types
{
	/** Logging messages*/
	static const Logging_Message* LOGGING;
	/** Messages for the entire view subsystem */
	static const View_Subsystem_Message* VIEW_SUBSYSTEM;
	/** Message for the view to create an option popup */
	static const Option_Popup_Message* OPTION_POPUP_REQUEST;

};


#endif