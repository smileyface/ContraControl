#include "../response_messages/view_request/option_popup_response_message.h"

Option_Popup_Response_Message::Option_Popup_Response_Message()
{ 
	selection_ = -1;
}

Option_Popup_Response_Message::Option_Popup_Response_Message(int selection, Option_Popup_Message responding_message)
{ 
	selection_ = selection;
	responding_message_ = responding_message;
}

int Option_Popup_Response_Message::get_selection()
{
	return selection_;
}

bool Option_Popup_Response_Message::this_message(Option_Popup_Message check_message)
{
	return false;
	//return responding_message_ == check_message;
}