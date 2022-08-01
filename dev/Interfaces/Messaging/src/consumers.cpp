#include "Messaging/consumers.h"
#include "../Utilities/Utilities/tools/classes.h"
#include <typeinfo>

bool true_ptr = true;
bool false_ptr = false;

Message_Consumer::Message_Consumer(bool* notify, const Internal_Message* mess)
{
	stale = notify;
	message_type = mess;
}
void Message_Consumer::notify()
{
	stale = &true_ptr;
}

void Message_Consumer::freshen()
{
	stale = &false_ptr;
}

bool Message_Consumer::correct_type(Internal_Message* mess)
{
	if(message_type == nullptr)
	{
		return false;
	}
	if(instanceof<Logging_Message>(message_type) && instanceof<Logging_Message>(mess))
	{
		return true;
	}
	if(instanceof<View_Subsystem_Message>(message_type) && instanceof<View_Subsystem_Message>(mess))
	{
		return true;
	}
	return false;
}