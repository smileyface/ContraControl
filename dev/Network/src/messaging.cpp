#include <vector>
#include <typeinfo>

#include "../messages.h"

Byte crc_sum_Table[256];

Packed_Message::Packed_Message(Network_Message in_message)
{
	message = in_message;
	header.message_id = in_message.get_type();
	size_t size = sizeof(header) + message.size() + sizeof(footer);
	if(size > 255)
	{
		//TODO: throw an error of invalid packet
	}
	else
	{
		header.length = size;
	}

	std::vector<Byte> packed_header = header.pack();
	std::vector<Byte> packed_body = message.pack();
	packet.insert(packet.end(), packed_header.begin(), packed_header.end());
	packet.insert(packet.end(), packed_body.begin(), packed_body.end());

	footer = Message_Footer(packet);
	std::vector<Byte> packed_footer = footer.pack();

	packet.insert(packet.end(), packed_footer.begin(), packed_footer.end());
}

Packed_Message::Packed_Message(Byte_Array pack)
{
	packet = pack;
	header.unpack(packet);
	message = node_messages::network_message_factory(header.message_id);
	message.unpack(packet, sizeof(header));
	footer.unpack(packet);
}

std::vector<Byte> Message_Header::pack()
{
	std::vector<Byte> packet;
	packet.push_back(message_start);
	packet.push_back((Byte) message_id);
	packet.push_back(length);

	return packet;
}

void Message_Header::unpack(std::vector<Byte> byte_array_message)
{
	message_start = byte_array_message[0];
	message_id = (MESSAGES) byte_array_message[1];
	length = byte_array_message[2];
}

#define WIDTH  (8 * sizeof(Byte))
#define TOPBIT (1 << (WIDTH - 1))
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */

void generate_crc_table()
{
	Byte  remainder;
	/*
	 * Compute the remainder of each possible dividend.
	 */
	for(int dividend = 0; dividend < 256; ++dividend)
	{
		/*
		 * Start with the dividend followed by zeros.
		 */
		remainder = dividend << (WIDTH - 8);

		/*
		 * Perform modulo-2 division, a bit at a time.
		 */
		for(Byte bit = 8; bit > 0; --bit)
		{
			/*
			 * Try to divide the current data bit.
			 */
			if(remainder & TOPBIT)
			{
				remainder = (remainder << 1) ^ POLYNOMIAL;
			}
			else
			{
				remainder = (remainder << 1);
			}
		}

		/*
		 * Store the result into the table.
		 */
		crc_sum_Table[dividend] = remainder;
	}
}

Message_Footer::Message_Footer(std::vector<Byte> head_and_body)
{
	Byte data = 0;
	Byte remainder = 0;
	/*
	 * Divide the message by the polynomial, a byte at a time.
	 */
	for(int byte = 0; byte < head_and_body.size(); ++byte)
	{
		data = head_and_body[byte] ^ (remainder >> (WIDTH - 8));
		remainder = crc_sum_Table[data] ^ (remainder << 8);
	}
	/*
	 * The final remainder is the CRC.
	 */
	chk1 = data;
	chk2 = remainder;
}

std::vector<Byte> Message_Footer::pack()
{
	std::vector<Byte> packet;
	packet.push_back(chk1);
	packet.push_back(chk2);
	return packet;
}

void Message_Footer::unpack(std::vector<Byte>)
{ }

std::vector<Byte> Packed_Message::get_packet()
{
	return packet;
}

void Packed_Message::get_message(Message_Header& head, Network_Message& mess, Message_Footer& foot)
{
	head = header;
	mess = message;
	foot = footer;
}

MESSAGES Packed_Message::get_message_type()
{
	return header.message_id;
}

Network_Message::Network_Message()
{
	type = MESSAGES::UNDEFINED;
}

Network_Message::Network_Message(MESSAGES message_type, std::vector<Network_Messaging_Type*> types)
{
	type = message_type;
	message = types;
}

std::vector<Byte> Network_Message::pack()
{
	Byte_Array packet;
	for(int i = 0; i < message.size(); i++)
	{
		Byte_Array sub_packet = message[i]->pack();
		packet.insert(packet.end(), sub_packet.begin(), sub_packet.end());
	}
	return packet;
}

size_t Network_Message::size()
{
	size_t message_size = 0;
	for(int i = 0; i < message.size(); i++)
	{
		message_size += message[i]->size();
	}
	return message_size;
}

void Network_Message::unpack(std::vector<Byte> byte_array, int header_size)
{
	//Remove Header
	byte_array.erase(byte_array.begin(), byte_array.begin() + header_size);
	for(int i = 0; i < message.size(); i++)
	{
		message[i]->unpack(byte_array);
	}
}

MESSAGES Network_Message::get_type()
{
	return type;
}

std::vector<Network_Messaging_Type*> Network_Message::get_message()
{
	return message;
}

Network_Messaging_Type& Network_Message::operator[](int index)
{
	return *message[index];
}

std::string get_message_type_string(MESSAGES type)
{
	switch(type)
	{
	case MESSAGES::NODE_HELLO:
		return "Node Hello";
	case MESSAGES::NODE_ACK:
		return "Node Acknowledge";
	case MESSAGES::NODE_GOODBYE:
		return "Node Goodbye";
	default:
		return "Undefined Message";
	}
}