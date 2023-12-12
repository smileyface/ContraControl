#include "../messages/node_communication.h"
#include "../network_main.h"

Network_Message node_messages::network_message_factory(MESSAGES message)
{
	switch (message)
	{
	case MESSAGES::NODE_HELLO:
		LOG_DEBUG("Node Hello message created");
		return Network_Message(message, { new Network_Address(), new Network_String() });
	case MESSAGES::NODE_ACK:
		LOG_DEBUG("Node Ack message created");
		return Network_Message(message, { new Network_String() });
	default:
		LOG_DEBUG("Unknown message attempted");
		return Network_Message(MESSAGES::UNDEFINED, { new Network_String(), new Network_Address(), new Network_Bool(), new Network_Byte(), new Network_Percent(), new Network_Word() });
	}
}

void node_messages::network_client_state_machine()
{
	switch (network::network_interface->get_status().status)
	{
	case NETWORK_STATUS::NETWORK_INITALIZED:
		Network_Message hello = node_messages::network_message_factory(MESSAGES::NODE_HELLO);
		hello[0] = network::network_interface->get_connection(local_connections::local).address;
		hello[1] = network::network_interface->get_hostname();
		network::send_message(local_connections::broadcast, hello);
		network::network_interface->set_network_state(NETWORK_STATUS::CLIENT_WAIT);
		break;
	}
}
