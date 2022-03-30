#include <vector>
#include <typeinfo>

#include "../messages.h"

byte crc_sum_Table[256];

MESSAGES PACKED_MESSAGE::get_message_enum_by_type()
{
	if (typeid(*message) == typeid(Node_Messages::NODE_HELLO))
	{
		return MESSAGES::NODE_HELLO;
	}
	else if (typeid(*message) == typeid(Node_Messages::NODE_ACK))
	{
		return MESSAGES::NODE_ACK;
	}
	return MESSAGES::UNDEFINED;
}

PACKED_MESSAGE::PACKED_MESSAGE(MESSAGE* in_message)
{
	this->message = in_message;
	header.message_id = get_message_enum_by_type();
	header.length = sizeof(header) + message->size() + sizeof(footer);

	std::vector<byte> packed_header = header.pack();
	std::vector<byte> packed_body = message->pack();
	packet.insert(packet.end(), packed_header.begin(), packed_header.end());
	packet.insert(packet.end(), packed_body.begin(), packed_body.end());

	footer = MESSAGE_FOOTER(packet);
	std::vector<byte> packed_footer = footer.pack();

	packet.insert(packet.end(), packed_footer.begin(), packed_footer.end());
}

std::vector<byte> MESSAGE_HEADER::pack()
{
	std::vector<byte> packet;
	packet.push_back(message_start);
	packet.push_back((byte)message_id);
	packet.push_back(length);

	return packet;
}

void MESSAGE_HEADER::unpack(std::vector<byte> byte_array_message)
{
	message_start = byte_array_message[0];
	message_id = (MESSAGES) byte_array_message[1];
	length = byte_array_message[2];
}

#define WIDTH  (8 * sizeof(byte))
#define TOPBIT (1 << (WIDTH - 1))
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */

void generate_crc_table()
{
	byte  remainder;
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
		for (byte bit = 8; bit > 0; --bit)
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


MESSAGE_FOOTER::MESSAGE_FOOTER(std::vector<byte> head_and_body)
{
	byte data = 0;
	byte remainder = 0;
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

std::vector<byte> MESSAGE_FOOTER::pack()
{
	std::vector<byte> packet;
	packet.push_back(chk1);
	packet.push_back(chk2);
	return packet;
}

void MESSAGE_FOOTER::unpack(std::vector<byte>)
{
}

std::vector<byte> PACKED_MESSAGE::get_packet()
{
	return packet;
}

PACKED_MESSAGE::PACKED_MESSAGE(std::vector<byte> pack)
{
	packet = pack;
	header.unpack(packet);
	switch (header.message_id)
	{
	case MESSAGES::NODE_HELLO:
		message = new Node_Messages::NODE_HELLO();
	}
	message->unpack(packet);
	footer.unpack(packet);
}

std::vector<byte> Message_String::pack()
{
	std::vector<byte> packet;
	packet.push_back(length);
	for (int i = 0; i < length; i++)
	{
		packet.push_back((unsigned char)str[i]);
	}
	return packet;
}


