#include <vector>
#include <typeinfo>

#include "../messages.h"

Byte crc_sum_Table[256];

PACKED_MESSAGE::PACKED_MESSAGE(MESSAGE in_message)
{
	message = in_message;
	header.message_id = in_message.get_type();
	size_t size = sizeof(header) + message.size() + sizeof(footer);
	if (size > 255)
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

	footer = MESSAGE_FOOTER(packet);
	std::vector<Byte> packed_footer = footer.pack();

	packet.insert(packet.end(), packed_footer.begin(), packed_footer.end());
}

PACKED_MESSAGE::PACKED_MESSAGE(Byte_Array pack)
{
	packet = pack;
	header.unpack(packet);
	message = node_messages::Network_Message_Factory(header.message_id);
	message.unpack(packet, sizeof(header));
	footer.unpack(packet);
}

std::vector<Byte> MESSAGE_HEADER::pack()
{
	std::vector<Byte> packet;
	packet.push_back(message_start);
	packet.push_back((Byte)message_id);
	packet.push_back(length);

	return packet;
}

void MESSAGE_HEADER::unpack(std::vector<Byte> byte_array_message)
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
	for (int dividend = 0; dividend < 256; ++dividend)
	{
		/*
		 * Start with the dividend followed by zeros.
		 */
		remainder = dividend << (WIDTH - 8);

		/*
		 * Perform modulo-2 division, a bit at a time.
		 */
		for (Byte bit = 8; bit > 0; --bit)
		{
			/*
			 * Try to divide the current data bit.
			 */
			if (remainder & TOPBIT)
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


MESSAGE_FOOTER::MESSAGE_FOOTER(std::vector<Byte> head_and_body)
{
	Byte data = 0;
	Byte remainder = 0;
	/*
	 * Divide the message by the polynomial, a byte at a time.
	 */
	for (int byte = 0; byte < head_and_body.size(); ++byte)
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

std::vector<Byte> MESSAGE_FOOTER::pack()
{
	std::vector<Byte> packet;
	packet.push_back(chk1);
	packet.push_back(chk2);
	return packet;
}

void MESSAGE_FOOTER::unpack(std::vector<Byte>)
{
}

std::vector<Byte> PACKED_MESSAGE::get_packet()
{
	return packet;
}

void PACKED_MESSAGE::get_message(MESSAGE_HEADER& head, MESSAGE& mess, MESSAGE_FOOTER& foot)
{
	head = header;
	mess = message;
	foot = footer;
}



MESSAGE::MESSAGE()
{
	type = MESSAGES::UNDEFINED;
}

MESSAGE::MESSAGE(MESSAGES message_type, std::vector<Network_Messaging_Type*> types)
{
	type = message_type;
	message = types;
}

std::vector<Byte> MESSAGE::pack()
{
	Byte_Array packet;
	for (int i = 0; i < message.size(); i++)
	{
		Byte_Array sub_packet = message[i]->pack();
		packet.insert(packet.end(), sub_packet.begin(), sub_packet.end());
	}
	return packet;
}

size_t MESSAGE::size()
{
	size_t message_size = 0;
	for (int i = 0; i < message.size(); i++)
	{
		message_size += message[i]->size();
	}
	return message_size;
}

void MESSAGE::unpack(std::vector<Byte> byte_array, int header_size)
{
	//Remove Header
	byte_array.erase(byte_array.begin(), byte_array.begin() + header_size);
	for (int i = 0; i < message.size(); i++)
	{
		message[i]->unpack(byte_array);
	}
}

MESSAGES MESSAGE::get_type()
{
	return type;
}

std::vector<Network_Messaging_Type*> MESSAGE::get_message()
{
	return message;
}

Network_Messaging_Type& MESSAGE::operator[](int index)
{
	return *message[index];
}
