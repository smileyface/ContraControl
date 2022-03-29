#include "../messages/node_communication.h"

Node_Messages::NODE_HELLO::NODE_HELLO(byte* in_addr, const char* in_id)
{
	id = Message_String(in_id);
	std::memcpy(addr, in_addr, sizeof(addr));
}

std::vector<byte> Node_Messages::NODE_HELLO::pack()
{
	std::vector<byte> packet;
	packet.push_back(addr[0]);
	packet.push_back(addr[1]);
	packet.push_back(addr[2]);
	packet.push_back(addr[3]);
	std::vector<byte> string_as_byte = id.pack();
	packet.insert(packet.end(), string_as_byte.begin(), string_as_byte.end());

	return packet;
}

size_t Node_Messages::NODE_HELLO::size()
{
	return sizeof(addr) + sizeof(id.length) + id.length;
}

Node_Messages::NODE_ACK::NODE_ACK(bool in_is_server, const char* in_id)
{
	is_server = in_is_server;
	id = Message_String(in_id);
}

std::vector<byte> Node_Messages::NODE_ACK::pack()
{
	std::vector<byte> packet;
	packet.push_back(is_server);
	std::vector<byte> string_as_byte = id.pack();
	packet.insert(packet.end(), string_as_byte.begin(), string_as_byte.end());
	return packet;
}
size_t Node_Messages::NODE_ACK::size()
{
	return sizeof(is_server) + sizeof(id.length) + id.length;
}


Node_Messages::NODE_CONNECT::NODE_CONNECT()
{

}

std::vector<byte> Node_Messages::NODE_CONNECT::pack()
{
	std::vector<byte> packet; 
	return packet;
}

size_t Node_Messages::NODE_CONNECT::size()
{
	return 0;
}
