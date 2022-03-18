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
#include "../network_main.h"

struct addrinfo hints;
WORD wVersionRequested = MAKEWORD(2, 2);

////////////////////////////////////////////////
///				HELPER FUNCTIONS
/// 
///	These are to help with windows specific 
/// networking. 
////////////////////////////////////////////////

NETWORK_ERRORS Windows_Network_Interface::set_error_state(int err_code)
{
	if(err_code == -1)
		err_code = WSAGetLastError();
	switch (err_code)
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
		return NETWORK_ERRORS::NETWORK_OPTION_ERROR;
	case WSAVERNOTSUPPORTED:
		return NETWORK_ERRORS::SYSTEM_INTERFACE_ERROR;
	case WSAHOST_NOT_FOUND:
		return NETWORK_ERRORS::INVALID_HOSTNAME;
	default:
		return NETWORK_ERRORS::UNKNOWN_ERROR;
	}
}

ipv4_addr Windows_Network_Interface::get_broadcast(ipv4_addr host_ip, ipv4_addr net_mask)
{
	return host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
}
ipv4_addr Windows_Network_Interface::get_interface_address(std::string hostname, std::string interfaces)
{
	struct addrinfo* hostinfo = NULL;
	std::vector<ipv4_addr> local_ips;

	std::string port = std::to_string(DEFAULT_PORT);
	if (getaddrinfo(hostname.c_str(), (char*)port.c_str(), &hints, &hostinfo) != 0)
	{
		status_state.set_error(set_error_state());
		throw NetworkErrorException();
	}
	int nCount = 0;
	for (struct addrinfo* ptr = hostinfo; ptr != NULL; ptr = ptr->ai_next)
	{
		char addr[16];
		struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
		inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, addr, 16);
		local_ips.push_back(std::string(addr));
		nCount++;
	}
	if (local_ips.size() == 1)
	{
		return local_ips[0];
	}
}

ipv4_addr Windows_Network_Interface::get_subnet_mask(SOCKET sock, ipv4_addr host_ip)
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

void Windows_Network_Interface::setup_broadcast_socket(Connection& connect, ipv4_addr host_ip)
{
	if (connect.sock == INVALID_SOCKET)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		throw NetworkErrorException();
	}

	char broadcast_opt_true = '1';
	if (setsockopt(connect.sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast_opt_true, sizeof(broadcast_opt_true)) < 0)
	{
		status_state.set_error(set_error_state());
		closesocket(connect.sock);
		connect.sock = INVALID_SOCKET;
		throw NetworkErrorException();

	}
}

ipv4_addr Windows_Network_Interface::convert_win_address(sockaddr_in* win_address)
{
	ipv4_addr gen_addr;
	gen_addr.S_un.S_addr = win_address->sin_addr.S_un.S_addr;
	return gen_addr;
}

bool Windows_Network_Interface::ipv4_compare(sockaddr_in* win_address, ipv4_addr gen_address)
{
	return win_address->sin_addr.S_un.S_addr == gen_address.S_un.S_addr;
}
////////////////////////////////////////////
///  WINDOWS_NETWORK_INTERFACE DEFINITIONS
/// 
/// Definitions for member functions of 
/// the Windows_Network_Interface class
////////////////////////////////////////////

Windows_Network_Interface::Windows_Network_Interface()
{
	local_connections::setup(connections);
	hostname = INVALID_HOSTNAME;
}

void Windows_Network_Interface::initalize()
{
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		status_state.set_error(set_error_state(err));
		throw NetworkErrorException();
	}

	char* host = (char*)hostname.c_str();
	gethostname(host, sizeof(host));
	hostname = host;

	setup_connection(local_connections::local, { IPPROTO_TCP, SOCK_STREAM, AF_INET });
	setup_connection(local_connections::broadcast, { IPPROTO_UDP, SOCK_DGRAM, AF_INET });
}

void Windows_Network_Interface::initalized()
{
	if (connections[local_connections::local].sock == INVALID_SOCKET)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		throw NetworkErrorException();
	}
	if (hostname == INVALID_HOSTNAME)
	{
		status_state.set_error(NETWORK_ERRORS::INVALID_HOSTNAME);
		throw NetworkErrorException();
	}
	status_state.set_status(NETWORK_STATUS::NETWORK_INITALIZED);
}

void Windows_Network_Interface::clean_up()
{
	for (auto i = connections.begin(); i != connections.end(); ++i)
	{
		closesocket(i->second.sock);
		i->second.sock = INVALID_SOCKET;
	}
	WSACleanup();
}

void Windows_Network_Interface::setup_connection(Connection_Id connection_name, Socket_Maker maker)
{
	connections[connection_name].sock = socket(maker.sock_family, maker.sock_type, maker.ip_protocol);
	if (connection_name == local_connections::broadcast)
	{
		ipv4_addr subnet_mask = get_subnet_mask(connections[local_connections::local].sock, connections[local_connections::local].address);
		connections[local_connections::broadcast].address = get_broadcast(connections[local_connections::local].address, subnet_mask);
		setup_broadcast_socket(connections[local_connections::broadcast], connections[local_connections::local].address);
	}
	if (connection_name == local_connections::local)
	{
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = maker.sock_family;
		hints.ai_socktype = maker.sock_type;
		hints.ai_protocol = maker.ip_protocol;
		connections[local_connections::local].address = get_interface_address(hostname, interfaces);
	}
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Interface IP: " + hostname + ": " + connections[local_connections::local].address.get_as_string(), "Network Initalizer"));
}


void Windows_Network_Interface::send(Connection_Id node_id, char* message)
{
	sendto(connections[node_id].sock, message, strlen(message) + 1, 0, (sockaddr*)&connections[node_id].address, sizeof(connections[node_id].address));
}

char* Windows_Network_Interface::listen(Connection_Id Connection_Id)
{
	return 0;
}

#endif // WIN32