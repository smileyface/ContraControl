#include "../messages/node_communication.h"

MESSAGE node_messages::Network_Message_Factory(MESSAGES message)
{
	switch (message)
	{
	case MESSAGES::NODE_HELLO:
		return MESSAGE(message, { new Network_Address(), new Network_String() });
	case MESSAGES::NODE_ACK:
		return MESSAGE(message, { new Network_String() });
	default:
		return MESSAGE(MESSAGES::UNDEFINED, { new Network_String(), new Network_Address(), new Network_Bool(), new Network_Byte(), new Network_Percent(), new Network_Word() });
	}
}
