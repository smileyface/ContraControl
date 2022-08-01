#include "../view.h"

#include "Messaging/message_relay.h"

View::View()
{
	view_consumer = new Message_Consumer(&stale, Message_Types::VIEW_SUBSYSTEM);
	Message_Relay::get_instance()->register_consumer(view_consumer);
}