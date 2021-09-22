#include <vector>
#include <typeinfo>

#include "Network/messages.h"

Node_Messages::NODE_HELLO::NODE_HELLO(unsigned char* in_addr, const char* in_id)
{
	id = Message_String(in_id);
	std::memcpy(addr, in_addr, sizeof(addr));
}

MESSAGES PACKED_MESSAGE::get_message_enum_by_type()
{
	if (typeid(message) == typeid(Node_Messages::NODE_HELLO))
	{
		return MESSAGES::NODE_HELLO;
	}
}

PACKED_MESSAGE::PACKED_MESSAGE(MESSAGE* in_message)
{
	header.message_id = get_message_enum_by_type();
	message = in_message;
}
