#include <limits>

#include "../console_format/console_option_popup.h"
#include "../view_type/option_view_type.h"
#include "Messaging/message_relay.h"

Option_View_Type::Option_View_Type()
{
}

void Option_View_Type::get_message()
{
	specified_message = Message_Relay::get_instance()->pop<Option_Popup_Message>(option_consumer);
	message.OPTIONS = specified_message.get_options();
	message.QUERY = specified_message.get_option_query();
}

void Option_View_Type::create()
{ 
	option_consumer = Message_Relay::get_instance()->register_consumer<Option_Popup_Message>();
}

void Option_View_Type::destroy()
{
	Message_Relay::get_instance()->deregister_consumer(option_consumer);
	option_consumer = nullptr;
}
