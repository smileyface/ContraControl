#include <string>
#include <stdlib.h>     /* atof */
#include <vector>

#include "../Utilities/Utilities/system.h"

#include "Network/system_interfaces/network_interface.h"
#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Network/system_interfaces/windows_network_interface.h"
#endif
#ifdef UNIX
#include "Network/system_interfaces/linux_network_interface.h"
#endif

/*This is where the Network Interface object is defined */
Network_Interface* network::network_interface;

bool network_is_init = false;
const std::string invalid_hostname = "INVALID";

void Network_Interface::set_client()
{
	is_server = false;
}

void Network_Interface::set_server()
{
	is_server = true;
}

ipv4_addr::ipv4_addr(char* str)
{
	size_t pos = 0;
	S_un = { 0,0,0,0 };
	std::string str_addr(str);
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

void network::init_network_interfaces()
{
#ifdef WIN32
	network::network_interface = new Windows_Network_Interface();
	network_interface->initalize();
#endif // IS_WIN32
#ifdef IS_UNIX
	network::network_interface = new Linux_Network_Interface();
#endif //IS_UNIX

	network_is_init = true;
}

/*This is where the Windows Network Interface object is defined*/
#ifdef WIN32

Windows_Network_Interface::Windows_Network_Interface()
{
	ListenSocket = INVALID_SOCKET;
	strcpy(hostname, invalid_hostname.c_str());
}

void Windows_Network_Interface::initalize()
{

	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	PHOSTENT hostinfo;

	if (WSAStartup(wVersionRequested, &wsaData) != 0)
		throw - 1;
	if (gethostname(hostname, sizeof(hostname)) != 0)
		throw - 1;
	if ((hostinfo = gethostbyname(hostname)) != NULL)
	{
		int nCount = 0;
		while (hostinfo->h_addr_list[nCount])
		{
			local_ips.push_back(inet_ntoa(*(
				struct in_addr*)hostinfo->h_addr_list[nCount]));
			nCount++;
		}
	}
	ListenSocket = socket(AF_INET, sock_type, ip_protocol);
}

bool Windows_Network_Interface::initalized()
{
	if (local_ips.size() == 0)
	{
		throw NETWORK_INITALIZED_ERRORS::ADAPTER_ERROR;
	}
	else if (ListenSocket == INVALID_SOCKET)
	{
		throw NETWORK_INITALIZED_ERRORS::SOCKET_INVALID;
	}
	else if (hostname == invalid_hostname)
	{
		throw NETWORK_INITALIZED_ERRORS::INVALID_HOSTNAME;
	}
	return true;
}

void Windows_Network_Interface::connect(ipv4_addr addr)
{

}

#endif // WIN32

/*This is where the Linux Network Interface object is defined*/
#ifdef UNIX

#endif //UNIX