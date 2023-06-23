#include "../view_messages/view_subsystem_message.h"

void View_Subsystem_Message::set_sender(SUBSYSTEM_ID_ENUM sender)
{
	request_from = sender;
}

SUBSYSTEM_ID_ENUM View_Subsystem_Message::get_sender()
{
	return request_from;
}
