#include "Messaging/consumers.h"
#include "../Utilities/Utilities/tools/classes.h"
#include <typeinfo>


Message_Consumer::Message_Consumer( const Internal_Message* mess)
{
	stale = false;
	message_type = mess;
}
Message_Consumer::~Message_Consumer()
{
	delete message_type;
}
void Message_Consumer::notify()
{
	stale = true;
}

void Message_Consumer::freshen()
{
	stale = false;
}

bool Message_Consumer::is_stale()
{
	return stale;
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