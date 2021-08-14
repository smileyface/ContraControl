#include "messaging.h"

namespace Node_Messages
{
	struct NODE_HELLO : MESSAGE
	{
		unsigned char addr[4];
		Message_String id;
		NODE_HELLO(unsigned char* in_addr, const char* in_id);
	};
}
