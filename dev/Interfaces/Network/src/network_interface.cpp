#include <string>
#include <stdlib.h>     /* atof */
#include <vector>

#include "../Utilities/Utilities/system.h"

#include "Network/system_interfaces/network_interface.h"
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Network/system_interfaces/windows_network_interface.h"
#endif
#ifdef __linux__
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
#ifdef _WIN32
	network::network_interface = new Windows_Network_Interface();
#endif // IS_WIN32
#ifdef __linux__
	network::network_interface = new Linux_Network_Interface();
#endif //__linux__
	network_interface->initalize();
	network_is_init = true;
}

void network::teardown_network_interfaces()
{
	network::network_interface->clean_up();
}

/*This is where the Windows Network Interface object is defined*/
#ifdef _WIN32

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
	ListenSocket = socket(sock_family, sock_type, ip_protocol);
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

void Windows_Network_Interface::clean_up()
{
	closesocket(ListenSocket);
	WSACleanup();
}

void Windows_Network_Interface::connect(ipv4_addr addr)
{
	throw std::exception("Not Implemented");
}

void Windows_Network_Interface::server_start()
{
	sockaddr_in service;
	//----------------------
   // The sockaddr_in structure specifies the address family,
   // IP address, and port for the socket that is being bound.
	service.sin_family = sock_family;
	service.sin_addr.s_addr = localhost.S_un.S_addr;
	service.sin_port = htons(656565);

	int iResult = bind(ListenSocket, (SOCKADDR*)&service, sizeof(service));
	if (iResult == SOCKET_ERROR) {
		throw NETWORK_INITALIZED_ERRORS::ERROR_ON_SOCKET_BIND;
	}
	//----------------------
	// Listen for incoming connection requests 
	// on the created socket. This is a blocking call.
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
		throw NETWORK_INITALIZED_ERRORS::ERROR_ON_SOCKET_LISTEN; 
}

#endif // WIN32

/*This is where the Linux Network Interface object is defined*/
#ifdef __linux__

void Linux_Network_Interface::connect(ipv4_addr addr)
{

}

void Linux_Network_Interface::initalize()
{

}

bool Linux_Network_Interface::initalized()
{
	return false;
}

#endif //__linux__