#include "Messaging/consumers.h"
#include "../Utilities/Utilities/tools/classes.h"
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
	if(instanceof<Logging_Message>(message_type) && instanceof<Logging_Message>(mess))
	{
		return true;
	}
	if(instanceof<Option_Popup_Message>(message_type) && instanceof<Option_Popup_Message>(mess))
	{
		return true;
	}
}