#include "../messages/node_communication.h"
#include "../network_main.h"

Network_Message node_messages::network_message_factory(MESSAGES message)
{
	switch (message)
	{
	case MESSAGES::NODE_HELLO:
		return Network_Message(message, { new Network_Address(), new Network_String() });
	case MESSAGES::NODE_ACK:
		return Network_Message(message, { new Network_String() });
	default:
		return Network_Message(MESSAGES::UNDEFINED, { new Network_String(), new Network_Address(), new Network_Bool(), new Network_Byte(), new Network_Percent(), new Network_Word() });
	}
}

Network_Message node_messages::network_communication_tree(MESSAGES type, Network_Message incoming)
{
	switch (type)
	{
	case MESSAGES::NODE_HELLO:
		Network_Message outgoing = network_message_factory(MESSAGES::NODE_ACK);
		network::send_message(local_connections::broadcast, outgoing);
	}
	return Network_Message();
}
