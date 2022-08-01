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

struct Message_Types
{
	static const Logging_Message* LOGGING;
	static const View_Subsystem_Message* VIEW_SUBSYSTEM;
	static const Option_Popup_Message* OPTION_POPUP_REQUEST;

};


#endif