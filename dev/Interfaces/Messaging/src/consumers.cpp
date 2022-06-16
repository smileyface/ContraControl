#include "Messaging/consumers.h"

#include <typeinfo>

Message_Consumer::Message_Consumer(bool& notify, Internal_Message* mess)
{
	stale = &notify;
	message_type = mess;
}
void Message_Consumer::notify()
{
	*stale = true;
}

void Message_Consumer::freshen()
{
	*stale = false;
}

bool Message_Consumer::correct_type(Internal_Message* mess)
{
	return typeid(mess) == typeid(message_type);
}