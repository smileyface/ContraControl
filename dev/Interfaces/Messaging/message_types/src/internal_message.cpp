#include "../internal_message_type.h"

Internal_Message::Internal_Message() :
	valid(false)
{ }

Internal_Message::~Internal_Message()
{ };


bool Internal_Message::is_valid()
{
	return valid;
}

void Internal_Message::validate()
{
	valid = true;
}