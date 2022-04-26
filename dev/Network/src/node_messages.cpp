#include "../messages/node_communication.h"
#include "../network_main.h"

std::pair<MESSAGES, Network_Message> message_buffer[8];

Network_Message node_messages::network_message_factory(MESSAGES message)
{
	switch(message)
	{
	case MESSAGES::NODE_HELLO:
		return Network_Message(message, { new Network_Address(), new Network_String() });
	case MESSAGES::NODE_ACK:
		return Network_Message(message, { new Network_String() });
	default:
		return Network_Message(MESSAGES::UNDEFINED, { new Network_String(), new Network_Address(), new Network_Bool(), new Network_Byte(), new Network_Percent(), new Network_Word() });
	}
}

void node_messages::network_client_state_machine()
{
	switch(network::network_interface->get_status().status)
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

void node_messages::listen_for_messages()
{
	while(network::is_running)
	{
	}
}