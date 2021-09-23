/*This is where the Windows Network Interface object is defined*/
#ifdef _WIN32

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <unordered_set>
#include <thread>

#include "../Utilities/Utilities/exceptions.h"

#include "Network/system_interfaces/windows_network_interface.h"

struct addrinfo hints;

Windows_Network_Interface::Windows_Network_Interface()
{
	sock = INVALID_SOCKET;
	hostname= invalid_hostname;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = sock_family;
	hints.ai_socktype = sock_type;
	hints.ai_protocol = ip_protocol;
}


void Windows_Network_Interface::initalize()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	struct addrinfo* hostinfo = NULL;

	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		status_state.set_error(NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR);
		throw NetworkErrorException();
	}
	char* host = (char*)hostname.c_str();
	gethostname(host, sizeof(host));
	if (host == invalid_hostname)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		throw NetworkErrorException();
	}
	std::string port = std::to_string(DEFAULT_PORT);
	getaddrinfo(host, (char*)port.c_str(), &hints, &hostinfo);
	int nCount = 0;
	for(struct addrinfo* ptr = hostinfo; ptr != NULL; ptr = ptr->ai_next)
	{
		char addr[16];
		struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
		inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, addr, 16);
		local_ips.push_back(std::string(addr));
		nCount++;
	}

	if (local_ips.size() == 1)
	{
		my_ip = local_ips[0];
	}
	sock = socket(sock_family, sock_type, ip_protocol);
	std::cout << sock << std::endl;
}

void Windows_Network_Interface::initalized()
{
	if (local_ips.size() == 0)
	{
		status_state.set_error(NETWORK_ERRORS::ADAPTER_ERROR);
		throw NetworkErrorException();
	}
	else if (sock == INVALID_SOCKET)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		throw NetworkErrorException();
	}
	else if (hostname == invalid_hostname)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		throw NetworkErrorException();
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Windows_Network_Interface::clean_up()
{
	closesocket(sock);
	WSACleanup();
}

ipv4_addr get_subnet_mask(SOCKET sock, ipv4_addr my_ip, Network_Status_State& status_state)
{
	INTERFACE_INFO InterfaceList[20];
	unsigned long nBytesReturned;
	if (WSAIoctl(sock, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
		sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
		switch (WSAGetLastError())
		{
		case WSA_IO_PENDING:
			status_state.set_error(NETWORK_ERRORS::SOCKET_BUSY);
			break;
		case WSAENETDOWN:
			status_state.set_error(NETWORK_ERRORS::NO_NETWORK_ERROR);
			break;
		case WSAENOTSOCK:
			status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
			break;
		default:
			status_state.set_error(NETWORK_ERRORS::ERROR_ON_SOCKET_BIND);
			break;
		}
		throw NetworkErrorException();
	}
	int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);

	ipv4_addr subnet_mask;
	for (int i = 0; i < nNumInterfaces; ++i) {

		if (Windows_Network_Interface::ipv4_compare((sockaddr_in*)&(InterfaceList[i].iiAddress), my_ip))
		{
			subnet_mask = Windows_Network_Interface::convert_win_address((sockaddr_in*)&(InterfaceList[i].iiNetmask));
		}
	}
	return subnet_mask;
}

void blast_arp(ipv4_addr current, DWORD& status)
{
	ULONG MacAddr[2];       /* for 6-byte hardware addresses */
	ULONG PhysAddrLen = 6;  /* default to length of six bytes */
	status = SendARP(current.S_un.S_addr, 0, &MacAddr, &PhysAddrLen);
}

std::vector<ipv4_addr> scan_for_possibilities(SOCKET sock, ipv4_addr my_addr, Network_Status_State& status_state)
{

	std::vector<ipv4_addr> thing;
	ipv4_addr subnet_mask = get_subnet_mask(sock, my_addr, status_state);
	/*ipv4_addr host_mask = ~get_subnet_mask(sock, my_addr, status_state).S_un.S_addr;
	ipv4_addr subnet = my_addr.S_un.S_addr & subnet_mask.S_un.S_addr;

	std::map<ipv4_addr, DWORD> addresses;

	ipv4_addr address;
	ipv4_addr top_addr = (ULONG_MAX & host_mask.S_un.S_addr) | subnet.S_un.S_addr;
	for (ipv4_addr i = subnet; i < top_addr; ++i)
	{
		address.S_un.S_addr = (i.S_un.S_addr & host_mask.S_un.S_addr) | subnet.S_un.S_addr;
		addresses[address] = ERROR_NOT_FOUND;
	}

	std::vector<std::thread> thread_queue;
	for (std::map<ipv4_addr, DWORD>::iterator x = addresses.begin(); x != addresses.end(); x++)
	{
		thread_queue.emplace_back(blast_arp, x->first, std::ref(addresses[x->first]));
	}
	for (std::vector<std::thread>::iterator x = thread_queue.begin(); x != thread_queue.end(); x++)
	{
		x->join();
	}
	for (std::map<ipv4_addr, DWORD>::iterator x = addresses.begin(); x != addresses.end(); x++)
	{
		if (addresses[x->first] == NO_ERROR || addresses[x->first] == ERROR_BUFFER_OVERFLOW)
		{
			thing.push_back(x->first);
		}
	}*/
	return thing;
}



void Windows_Network_Interface::connect_to_server(ipv4_addr addr)
{
	struct addrinfo* result = NULL;
	int iResult;

	// Resolve the server address and port
	iResult = getaddrinfo(addr.get_as_string().c_str(), std::to_string(DEFAULT_PORT).c_str(), &hints, &result);
	if (iResult != 0) {
		status_state.set_error(NETWORK_ERRORS::ADAPTER_ERROR);
	}

	// Attempt to connect to an address until one succeeds
	for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		accepted_connections[addr] = socket(ptr->ai_family, ptr->ai_socktype,
											ptr->ai_protocol);
		if (accepted_connections[addr] == INVALID_SOCKET) {
			status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		}

		// Connect to server.
		iResult = connect(accepted_connections[addr], ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(accepted_connections[addr]);
			accepted_connections[addr] = INVALID_SOCKET;
			continue;
		}
		status_state.set_status(NETWORK_STATUS::CLIENT_CONNECT);
		break;
	}

	freeaddrinfo(result);
}

void Windows_Network_Interface::scan_for_server()
{

	std::vector<ipv4_addr> possibilites = scan_for_possibilities(sock, my_ip, status_state);

	std::vector<std::thread> thread_queue;
	/*for (int i = 0; i < possibilites.size(); i++)
	{
		thread_queue.emplace_back(&Windows_Network_Interface::connect_to_server, this, possibilites[i]);
	}
	for (std::vector<std::thread>::iterator x = thread_queue.begin(); x != thread_queue.end(); x++)
	{
		x->join();
	}*/
}

void Windows_Network_Interface::server_start()
{
	sockaddr_in service;
	//----------------------
   // The sockaddr_in structure specifies the address family,
   // IP address, and port for the socket that is being bound.
	service.sin_family = sock_family;
	service.sin_addr.s_addr = localhost.S_un.S_addr;
	service.sin_port = htons(DEFAULT_PORT);

	int iResult = bind(sock, (SOCKADDR*)&service, sizeof(service));
	if (iResult == SOCKET_ERROR) {
		status_state.set_error(NETWORK_ERRORS::ERROR_ON_SOCKET_BIND);
	}
	//----------------------
	// Listen for incoming connection requests 
	// on the created socket. This is a blocking call.
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
		status_state.set_error(NETWORK_ERRORS::ERROR_ON_SOCKET_LISTEN);
}

#endif // WIN32