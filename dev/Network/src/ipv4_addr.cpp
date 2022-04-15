#include <vector>
#include <climits>

#include "../system_interfaces/types/ipv4_addr.h"

IPV4_Addr::IPV4_Addr()
{
	S_un.S_addr = ULONG_MAX;
}

IPV4_Addr::IPV4_Addr(std::string str_addr)
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

IPV4_Addr::IPV4_Addr(unsigned long l1)
{
	S_un.S_addr = l1;
}

void IPV4_Addr::operator=(const unsigned char* ca)
{
	S_un.S_un_b.s_b1 = ca[0];
	S_un.S_un_b.s_b2 = ca[1];
	S_un.S_un_b.s_b3 = ca[2];
	S_un.S_un_b.s_b4 = ca[3];
}

bool IPV4_Addr::operator==(const IPV4_Addr ad)
{
	return S_un.S_un_b.s_b1 == ad.S_un.S_un_b.s_b1 &&
		   S_un.S_un_b.s_b2 == ad.S_un.S_un_b.s_b2 &&
		   S_un.S_un_b.s_b3 == ad.S_un.S_un_b.s_b3 &&
		   S_un.S_un_b.s_b4 == ad.S_un.S_un_b.s_b4;
}

std::string IPV4_Addr::get_as_string()
{
	char buffer[20];
	sprintf(buffer, "%u.%u.%u.%u", S_un.S_un_b.s_b1,
		S_un.S_un_b.s_b2,
		S_un.S_un_b.s_b3,
		S_un.S_un_b.s_b4);
	return buffer;
}

unsigned char* IPV4_Addr::get_addr_bytes()
{
	return reinterpret_cast<unsigned char*>(&S_un.S_un_b);
}
