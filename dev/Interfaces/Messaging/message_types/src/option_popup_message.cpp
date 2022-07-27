#include "../view_messages/view_request/option_popup_message.h"

Option_Popup_Message::Option_Popup_Message()
{
}

Option_Popup_Message::Option_Popup_Message(SUBSYSTEM_ID_ENUM from, std::vector<std::string> list_of_options)
{
	set_sender(from);
	options = list_of_options;
}

Option_List Option_Popup_Message::get_options()
{
	return options;
}

void Option_Popup_Message::placeholder()
{

}