#include <vector>
#include <climits>

#include "Network/system_interfaces/types/ipv4_addr.h"

ipv4_addr::ipv4_addr()
{
	S_un.S_addr = ULONG_MAX;
}

ipv4_addr::ipv4_addr(std::string str_addr)
{

	size_t pos = 0;
	S_un = { 0,0,0,0 };
	std::vector<unsigned char> bytes;
	while ((pos = str_addr.find(".")) != std::string::npos) {
		char byte = atoi(str_addr.substr(0, pos).c_str());
		bytes.push_back(static_cast<unsigned char>(byte));
		str_addr.erase(0, pos + 1);
	}
	char byte = atoi(str_addr.c_str());
	bytes.push_back(static_cast<unsigned char>(byte));


	if (bytes.size() == 4)
	{
		S_un.S_un_b.s_b1 = bytes[0];
		S_un.S_un_b.s_b2 = bytes[1];
		S_un.S_un_b.s_b3 = bytes[2];
		S_un.S_un_b.s_b4 = bytes[3];
	}
}

ipv4_addr::ipv4_addr(unsigned long l1)
{
	S_un.S_addr = l1;
}

ipv4_addr::ipv4_addr(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4)
{
	S_un.S_un_b.s_b1 = b1;
	S_un.S_un_b.s_b2 = b2;
	S_un.S_un_b.s_b3 = b3;
	S_un.S_un_b.s_b4 = b4;
}

ipv4_addr ipv4_addr::operator++()
{
	if (this->S_un.S_un_b.s_b2 == 255 && this->S_un.S_un_b.s_b3 == 255 && this->S_un.S_un_b.s_b4 == 255)
	{
		this->S_un.S_un_b.s_b1++;
	}
	if (this->S_un.S_un_b.s_b3 == 255 && this->S_un.S_un_b.s_b4 == 255)
	{
		this->S_un.S_un_b.s_b2++;
	}
	if (this->S_un.S_un_b.s_b4 == 255)
	{
		this->S_un.S_un_b.s_b3++;
	}
	this->S_un.S_un_b.s_b4++;
	return *this;
}
bool ipv4_addr::operator<(const ipv4_addr& d) const
{
	return S_un.S_addr < d.S_un.S_addr;
}
void ipv4_addr::operator=(const unsigned long& D)
{
	S_un.S_addr = D;
}
void ipv4_addr::operator=(const char* ca)
{
	S_un.S_un_b.s_b1 = ca[0];
	S_un.S_un_b.s_b2 = ca[1];
	S_un.S_un_b.s_b3 = ca[2];
	S_un.S_un_b.s_b4 = ca[3];
}
std::string ipv4_addr::get_as_string()
{
	char buffer[20];
	sprintf(buffer, "%u.%u.%u.%u", S_un.S_un_b.s_b1,
		S_un.S_un_b.s_b2,
		S_un.S_un_b.s_b3,
		S_un.S_un_b.s_b4);
	return buffer;
}

unsigned char* ipv4_addr::get_addr_bytes()
{
	return reinterpret_cast<unsigned char*>(&S_un.S_un_b);
}
