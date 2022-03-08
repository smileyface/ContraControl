/*This is where the Windows Network Interface object is defined*/
#ifdef _WIN32

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <unordered_set>
#include <thread>

#include "../Utilities/Utilities/exceptions.h"

#include "../system_interfaces/windows_network_interface.h"

struct addrinfo hints;

////////////////////////////////////////////////
///				HELPER FUNCTIONS
/// 
///	These are to help with windows specific 
/// networking. 
////////////////////////////////////////////////

NETWORK_ERRORS set_error_state()
{
	switch (WSAGetLastError())
	{
	case WSAEFAULT:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	case WSANOTINITIALISED:
		return NETWORK_ERRORS::UNINITALIZED_INTERFACE;
	case WSAEINPROGRESS:
		return NETWORK_ERRORS::SOCKET_BUSY;
	case WSAENETDOWN:
		return NETWORK_ERRORS::NO_NETWORK_ERROR;
	case WSAENOTSOCK:
		return NETWORK_ERRORS::SOCKET_INVALID;
	case WSAEINVAL:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	case WSAENOPROTOOPT:
		return NETWORK_ERRORS::NETWORK_CODE_ERROR;
	default:
		return NETWORK_ERRORS::UNKNOWN_ERROR;
	}
}

ipv4_addr get_broadcast(ipv4_addr host_ip, ipv4_addr net_mask)
{
	return host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
}

ipv4_addr get_subnet_mask(SOCKET sock, ipv4_addr host_ip, Network_Status_State& status_state)
{
	INTERFACE_INFO InterfaceList[20];
	unsigned long nBytesReturned;
	if (WSAIoctl(sock, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
		sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
		status_state.set_error(set_error_state());
		throw NetworkErrorException();
	}
	int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);

	ipv4_addr subnet_mask;
	for (int i = 0; i < nNumInterfaces; ++i) {

		if (Windows_Network_Interface::ipv4_compare((sockaddr_in*)&(InterfaceList[i].iiAddress), host_ip))
		{
			subnet_mask = Windows_Network_Interface::convert_win_address((sockaddr_in*)&(InterfaceList[i].iiNetmask));
		}
	}
	return subnet_mask;
}

////////////////////////////////////////////
///  WINDOWS_NETWORK_INTERFACE DEFINITIONS
/// 
/// Definitions for member functions of 
/// the Windows_Network_Interface class
////////////////////////////////////////////

Windows_Network_Interface::Windows_Network_Interface()
{
	sock = INVALID_SOCKET;
	hostname = invalid_hostname;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = sock_family;
	hints.ai_socktype = sock_type;
	hints.ai_protocol = ip_protocol;
}

void Windows_Network_Interface::initalize()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;

	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		status_state.set_error(NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR);
		throw NetworkErrorException();
	}

	sock = socket(sock_family, sock_type, ip_protocol);
	set_my_ip();
	subnet_mask = get_subnet_mask(sock, host_ip, status_state);
	broadcast_ip = get_broadcast(host_ip, subnet_mask);
}

void Windows_Network_Interface::initalized()
{
	if (sock == INVALID_SOCKET)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		throw NetworkErrorException();
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Windows_Network_Interface::clean_up()
{
	closesocket(sock);
	WSACleanup();
}

void Windows_Network_Interface::set_my_ip()
{
	struct addrinfo* hostinfo = NULL;
	char* host = (char*)hostname.c_str();
	while (WSAIsBlocking())
	{
		printf("Blocking");
	}
	gethostname(host, sizeof(host));

	if (host == invalid_hostname)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		throw NetworkErrorException();
	}
	std::string port = std::to_string(DEFAULT_PORT);
	getaddrinfo(host, (char*)port.c_str(), &hints, &hostinfo);
	int nCount = 0;
	for (struct addrinfo* ptr = hostinfo; ptr != NULL; ptr = ptr->ai_next)
	{
		char addr[16];
		struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
		inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, addr, 16);
		local_ips.push_back(std::string(addr));
		nCount++;
	}
	hostname = host;
	if (local_ips.size() == 1)
	{
		host_ip = local_ips[0];
	}
	//network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG, "Interface IP: " + hostname + ": " + host_ip.get_as_string(), "Network Initalizer"));
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
	SOCKET broadcast_sock;
	broadcast_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	sockaddr_in bcast_addr;
	bcast_addr.sin_family = AF_INET;
	bcast_addr.sin_port = htons(DEFAULT_PORT);
	bcast_addr.sin_addr.s_addr = inet_addr(broadcast_ip.get_as_string().c_str());

	if (broadcast_sock == INVALID_SOCKET)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		throw NetworkErrorException();
	}

	char broadcast_opt_true = '1';
	if (setsockopt(broadcast_sock, SOL_SOCKET, SO_BROADCAST,(char *) &broadcast_opt_true, sizeof(broadcast_opt_true)) < 0)
	{
		//cout << "Error in setting Broadcast option";
		status_state.set_error(set_error_state());
		closesocket(sock);
		throw NetworkErrorException();

	}
	//TODO: Turn this into a real node hello packet.
	/*Testing things for now*/
	char sendMSG[] = "NODE_HELLO";



	char recvbuff[50] = "";

	int recvbufflen = 50;

	sendto(broadcast_sock, sendMSG, strlen(sendMSG) + 1, 0, (sockaddr*)&bcast_addr, sizeof(bcast_addr));
	//send_periodic(broadcast_sock, NODE_HELLO, 2000, till_found);
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