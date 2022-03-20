#include <vector>
#include <typeinfo>

#include "Network/messages.h"

Node_Messages::NODE_HELLO::NODE_HELLO(unsigned char* in_addr, const char* in_id)
{
	id = Message_String(in_id);
	std::memcpy(addr, in_addr, sizeof(addr));
}

Node_Messages::NODE_ACK::NODE_ACK(bool in_is_server, const char* in_id)
{
	is_server = in_is_server;
	id = Message_String(in_id);
}

MESSAGES PACKED_MESSAGE::get_message_enum_by_type()
{
	if (typeid(message) == typeid(Node_Messages::NODE_HELLO))
	{
		return MESSAGES::NODE_HELLO;
	}
	return MESSAGES::UNDEFINED;
}

PACKED_MESSAGE::PACKED_MESSAGE(MESSAGE* in_message)
{
	header.message_id = get_message_enum_by_type();
	message = in_message;
}

unsigned char* pack()
{
	return 0;
}
