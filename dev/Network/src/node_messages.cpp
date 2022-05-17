#include "../messages/node_communication.h"
#include "../network_main.h"

std::vector<std::pair<MESSAGES, Network_Message>> message_buffer;

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

void node_messages::listen_for_messages_from_node(Connection sock)
{
	while(sock.rec != RECIEVE_STATE::CLOSE_CONNECTION && network::is_running())
	{
		Byte_Array recieved = network::network_interface->receive(sock.sock, 1);
		if(recieved[0] != 0x65)
		{
			continue;
		}
		Byte_Array rec_header = network::network_interface->receive(sock.sock, 2);
		Byte_Array message = network::network_interface->receive(sock.sock, rec_header[1] - 3);
		message.insert(message.begin(), rec_header.begin(), rec_header.end());
		Unpacked_Message p_message(message);
		message_buffer.push_back(std::make_pair(p_message.get_header().message_id, p_message.get_message()));
	}
}