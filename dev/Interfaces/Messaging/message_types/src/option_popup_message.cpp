#include "../view_messages/view_request/option_popup_message.h"

Option_Popup_Message::Option_Popup_Message() :
	option_query_(""),
	options_({})
{ }

Option_Popup_Message::Option_Popup_Message(SUBSYSTEM_ID_ENUM from, std::string option_query, Option_List list_of_options)
{ 
	set_sender(from);
	option_query_ = option_query;
	options_ = list_of_options;
}

Option_List Option_Popup_Message::get_options()
{
	return options_;
}

std::string Option_Popup_Message::get_option_query()
{
	return option_query_;
}