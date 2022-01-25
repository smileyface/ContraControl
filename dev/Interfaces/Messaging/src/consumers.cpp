#include "Messaging/consumers.h"

Message_Consumer::Message_Consumer(bool* notify)
{
	stale = notify;
}
void Message_Consumer::notify()
{
	*stale = true;
}

void Message_Consumer::freshen()
{
	*stale = false;
}
