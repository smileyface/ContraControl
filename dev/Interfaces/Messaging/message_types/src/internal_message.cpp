#include "../internal_message_type.h"
#include "../id_pool.h"

Internal_Message::Internal_Message() :
	valid(false),
	unique_message_id(MESSAGE_ID.get())
{ }

Internal_Message::~Internal_Message()
{ };

bool Internal_Message::operator!=(Internal_Message* ptr_value)
{
	return this != ptr_value;
}

bool Internal_Message::operator==(Internal_Message* ptr_value)
{
	return this->unique_message_id == ptr_value->unique_message_id;
}

bool Internal_Message::is_valid()
{
	return valid;
}

void Internal_Message::validate()
{
	valid = true;
}
