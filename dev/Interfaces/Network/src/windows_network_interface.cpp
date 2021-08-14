/*This is where the Windows Network Interface object is defined*/
#ifdef _WIN32

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <unordered_set>
#include <thread>

#include "Network/system_interfaces/windows_network_interface.h"


Windows_Network_Interface::Windows_Network_Interface()
{
	sock = INVALID_SOCKET;
	strcpy(hostname, invalid_hostname.c_str());
}


void Windows_Network_Interface::initalize()
{

	WORD wVersionRequested = MAKEWORD(2, 2);
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

	if (local_ips.size() == 1)
	{
		my_ip = local_ips[0];
	}
	sock = socket(sock_family, sock_type, ip_protocol);
}

bool Windows_Network_Interface::initalized()
{
	if (local_ips.size() == 0)
	{
		throw NETWORK_INITALIZED_ERRORS::ADAPTER_ERROR;
	}
	else if (sock == INVALID_SOCKET)
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
	closesocket(sock);
	WSACleanup();
}

ipv4_addr get_subnet_mask(SOCKET sock, ipv4_addr my_ip)
{
	INTERFACE_INFO InterfaceList[20];
	unsigned long nBytesReturned;
	if (WSAIoctl(sock, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
		sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {

		throw 1;
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
	IPAddr DestIp = inet_addr(current.get_as_string().c_str());
	IPAddr SrcIp = 0;       /* default for src ip */
	ULONG MacAddr[2];       /* for 6-byte hardware addresses */
	ULONG PhysAddrLen = 6;  /* default to length of six bytes */
	status = SendARP(DestIp, SrcIp, &MacAddr, &PhysAddrLen);
}

std::vector<ipv4_addr> scan_for_possibilities(SOCKET sock, ipv4_addr my_addr)
{
	ipv4_addr subnet_mask = get_subnet_mask(sock, my_addr);
	ipv4_addr host_mask = ~get_subnet_mask(sock, my_addr).S_un.S_addr;
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
	std::vector<ipv4_addr> thing;
	for (std::map<ipv4_addr, DWORD>::iterator x = addresses.begin(); x != addresses.end(); x++)
	{
		if (addresses[x->first] == NO_ERROR || addresses[x->first] == ERROR_BUFFER_OVERFLOW)
		{
			thing.push_back(x->first);
		}
	}
	return thing;
}



void Windows_Network_Interface::connect_to_server(ipv4_addr addr)
{
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	int iResult;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(addr.get_as_string().c_str(), std::to_string(DEFAULT_PORT).c_str(), &hints, &result);
	if (iResult != 0) {
		throw NETWORK_INITALIZED_ERRORS::ADAPTER_ERROR;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		accepted_connections[addr] = socket(ptr->ai_family, ptr->ai_socktype,
											ptr->ai_protocol);
		if (accepted_connections[addr] == INVALID_SOCKET) {
			throw NETWORK_INITALIZED_ERRORS::SOCKET_INVALID;
		}

		// Connect to server.
		iResult = connect(accepted_connections[addr], ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(accepted_connections[addr]);
			accepted_connections[addr] = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);
}

void Windows_Network_Interface::scan_for_server()
{

	std::vector<ipv4_addr> possibilites = scan_for_possibilities(sock, my_ip);

	std::vector<std::thread> thread_queue;
	for (int i = 0; i < possibilites.size(); i++)
	{
		thread_queue.emplace_back(&Windows_Network_Interface::connect_to_server, possibilites[i]);
	}
	for (std::vector<std::thread>::iterator x = thread_queue.begin(); x != thread_queue.end(); x++)
	{
		x->join();
	}
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
		throw NETWORK_INITALIZED_ERRORS::ERROR_ON_SOCKET_BIND;
	}
	//----------------------
	// Listen for incoming connection requests 
	// on the created socket. This is a blocking call.
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
		throw NETWORK_INITALIZED_ERRORS::ERROR_ON_SOCKET_LISTEN;
}

#endif // WIN32