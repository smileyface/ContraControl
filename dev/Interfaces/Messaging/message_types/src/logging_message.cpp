#include "Messaging/message_types/logging_message.h"


Logging_Message::Logging_Message(MESSAGE_PRIORITY pri, std::string msg, std::string loc)
{
	priority = pri;
	message = msg;
	location = loc;
}

std::string message_priority_as_string(MESSAGE_PRIORITY al)
{
	std::string level;
	switch(al)
	{
	case MESSAGE_PRIORITY::SEVERE_MESSAGE:
		return "SEVERE";
	case MESSAGE_PRIORITY::INFO_MESSAGE:
		return "INFO";
	case MESSAGE_PRIORITY::ERROR_MESSAGE:
		return "ERROR";
	case MESSAGE_PRIORITY::DEBUG_MESSAGE:
		return "DEBUG";
	default:
		return "UNHANDLED PRIORITY";
	}
	return level;
}

std::string Logging_Message::get_message()
{
	return message;
}

std::string Logging_Message::get_location()
{
	return location;
}

std::string Logging_Message::get_priority_string()
{
	return message_priority_as_string(priority);
}

MESSAGE_PRIORITY Logging_Message::get_priority()
{
	return priority;
}



