#include "../messages/types/basic_types.h"

#include <stdexcept>

Byte Network_Byte::size()
{
	return 1;
}

Byte_Array Network_Byte::pack()
{
	if (number < 256)
	{
		return { (Byte)number };
	}
	else
	{
		throw std::length_error("");
	}
	return Byte_Array();
}

void Network_Byte::unpack(Byte_Array& byte_string)
{
	number = byte_string[0];
	byte_string.erase(byte_string.begin());
}

void Network_Byte::operator=(Byte assigner)
{
	number = assigner;
}

Byte Network_Word::size()
{
	return 2;
}

Byte_Array Network_Word::pack()
{
	if (number > INT16_MIN && number < INT16_MAX)
	{
		Byte high = number & 0xff00;
		Byte low = number & 0x00ff;
		return { low, high };
	}
	else
	{
		throw std::length_error("");
	}
	return Byte_Array();
}

void Network_Word::unpack(Byte_Array& byte_string)
{
	signed short result = 0;
	result = (result << 8) + byte_string[1]; // heigh byte
	result = (result << 8) + byte_string[0]; // low byte
	byte_string.erase(byte_string.begin(), byte_string.begin()+1);
}

void Network_Word::operator=(int assigner)
{
	number = assigner;
}

Byte Network_String::size()
{
	return length + 1;
}

Byte_Array Network_String::pack()
{
	Byte_Array packet;
	packet.push_back(length);
	//removes the null termination.
	for (int i = 0; i < length; i++)
	{
		packet.push_back((unsigned char)message[i]);
	}
	return packet;
}

void Network_String::unpack(Byte_Array& byte_string)
{
	length = byte_string[0];
	byte_string.erase(byte_string.begin());
	for (int i = 0; i < length; i++)
	{
		message += byte_string[i];
	}
}

void Network_String::operator=(std::string assigner)
{
	length = assigner.size();
	message = assigner;
}

std::pair <Byte, std::string> Network_String::get_data()
{
	return std::make_pair(length, message);
}

Byte Network_Bool::size()
{
	return 1;
}

Byte_Array Network_Bool::pack()
{
	Byte_Array packet(boolean);
	return packet;
}

void Network_Bool::unpack(Byte_Array& byte_string)
{
	boolean = byte_string[0];
	byte_string.erase(byte_string.begin());
}

void Network_Bool::operator=(bool assigner)
{
	boolean = assigner;
}

Byte Network_Address::size()
{
	return sizeof(address.S_un.S_un_b);
}

Byte_Array Network_Address::pack()
{
	Byte_Array packet;
	for (int i = 0; i < size(); i++)
	{
		packet.push_back(address.get_addr_bytes()[i]);
	}
	return packet;
}

void Network_Address::unpack(Byte_Array& byte_string)
{
	Byte thing[4] = { byte_string[0], byte_string[1], byte_string[2], byte_string[3] };
	address = thing;

	byte_string.erase(byte_string.begin(), byte_string.begin() + 4);
}

void Network_Address::operator=(ipv4_addr assigner)
{
	address = assigner;
}

ipv4_addr Network_Address::get_data()
{
	return address;
}
