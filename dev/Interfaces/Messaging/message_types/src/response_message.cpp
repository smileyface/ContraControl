#include "../response_messages/response_message.h"

Response_Message::Response_Message()
{
	receipt = new int(0);
}

bool Response_Message::this_message(Message_Receipt check_message)
{
	return check_message == receipt;
}

Message_Receipt Response_Message::get_receipt()
{
	return receipt;
}
