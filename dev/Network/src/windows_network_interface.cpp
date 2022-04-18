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

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

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
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Error code " + std::to_string(err_code) + " thrown", "Windows Network Error Handle"));

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

IPV4_Addr Windows_Network_Interface::get_broadcast(IPV4_Addr host_ip, IPV4_Addr net_mask)
{
	IPV4_Addr bcast;
	bcast = host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
	return bcast;
}
IPV4_Addr Windows_Network_Interface::get_interface_address(std::string hostname, std::string interfaces)
{
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Searching for " + interfaces, "Interface Finding"));

    /* Declare and initialize variables */

    DWORD dwRetVal = 0;

	std::wstring a(interfaces.begin(), interfaces.end());

    // Set the flags to pass to GetAdaptersAddresses
    ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

    // default to unspecified address family (both)
    ULONG family = AF_INET;

    LPVOID lpMsgBuf = NULL;

    ULONG outBufLen = 0;
    ULONG Iterations = 0;

	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
	IPV4_Addr found_ip;

    struct sockaddr_in* sockaddr_ipv4 = 0;
    // Allocate a 15 KB buffer to start with.
    outBufLen = WORKING_BUFFER_SIZE;

    pAddresses = (IP_ADAPTER_ADDRESSES*)MALLOC(outBufLen);

    dwRetVal =
        GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);


    if (dwRetVal != 0) 
	{
		status_state.set_error(set_error_state(dwRetVal));
		network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Cannot get adapter address", "Getting IP Addr Table"));
        FREE(pAddresses);
        pAddresses = NULL;
		throw NetworkErrorException();
    }

	for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses; pCurrAddresses = pCurrAddresses->Next)
	{
		IN_ADDR IPAddr{};
		std::wstring thing(pCurrAddresses->FriendlyName);
		std::wstring dns(pCurrAddresses->DnsSuffix);
		network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Interface " + std::string(thing.begin(), thing.end()) + " found", "Interface Finding"));
		if (found_ip == INVALID_ADDRESS && pCurrAddresses->FriendlyName == a && pCurrAddresses->FirstUnicastAddress->Address.lpSockaddr->sa_family == family)
		{
			std::string friend_name = std::string(thing.begin(), thing.end());
			sockaddr_in* address = (sockaddr_in*)pCurrAddresses->FirstUnicastAddress->Address.lpSockaddr;
			found_ip.S_un.S_addr = address->sin_addr.S_un.S_addr;
			// now get it back and print it
			std::string message = friend_name + ": " + found_ip.get_as_string();
			network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, message, "Local interface connection"));
		}
	}
	if (found_ip == INVALID_ADDRESS)
	{
		status_state.set_error(NETWORK_ERRORS::ADDRESS_ERROR);
		throw NetworkErrorException();
	}
    if (pAddresses) 
    {
        FREE(pAddresses);
    }
    return found_ip;
}

IPV4_Addr Windows_Network_Interface::get_subnet_mask(SOCKET sock, IPV4_Addr host_ip)
{
	INTERFACE_INFO InterfaceList[20] = { 0 };
	unsigned long nBytesReturned;
	if (WSAIoctl(sock, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
		sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
		status_state.set_error(set_error_state());
		throw NetworkErrorException();
	}
	int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);

	IPV4_Addr subnet_mask;
	for (int i = 0; i < nNumInterfaces; ++i) {

		if (Windows_Network_Interface::ipv4_compare((sockaddr_in*)&(InterfaceList[i].iiAddress), host_ip))
		{
			subnet_mask = Windows_Network_Interface::convert_win_address((sockaddr_in*)&(InterfaceList[i].iiNetmask));
		}
	}
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Subnet Mask: " + subnet_mask.get_as_string(), "Subnet Mask Finder"));
	return subnet_mask;
}

void Windows_Network_Interface::setup_broadcast_socket(Connection& connect, IPV4_Addr host_ip)
{
	if (connect.sock == INVALID_SOCKET)
	{
		status_state.set_error(NETWORK_ERRORS::SOCKET_INVALID);
		network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Broadcast Sock Invalid", "Broadcast Socket check"));
		throw NetworkErrorException();
	}
	char broadcast_opt_true = '1';
	if (setsockopt(connect.sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast_opt_true, sizeof(broadcast_opt_true)) < 0)
	{
		status_state.set_error(set_error_state());
		network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Issue setting up broadcast socket", "Broadcast setsockopt"));
		closesocket(connect.sock);
		connect.sock = INVALID_SOCKET;
		throw NetworkErrorException();

	}
}

IPV4_Addr Windows_Network_Interface::convert_win_address(sockaddr_in* win_address)
{
	IPV4_Addr gen_addr;
	gen_addr.S_un.S_addr = win_address->sin_addr.S_un.S_addr;
	return gen_addr;
}

bool Windows_Network_Interface::ipv4_compare(sockaddr_in* win_address, IPV4_Addr gen_address)
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

	interfaces = "Loopback Pseudo-Interface 1";
}

void Windows_Network_Interface::initalize()
{
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Error starting WSA", "Initalized"));
		status_state.set_error(set_error_state(err));
		throw NetworkErrorException();
	}

	char* host = (char*)hostname.c_str();
	err = gethostname(host, 50);
	if (err != 0)
	{
		network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Error getting hostname", "Initalized"));
		status_state.set_error(set_error_state(err));
		throw NetworkErrorException();
	}
	hostname = host;

	setup_connection(local_connections::local, { IPPROTO_TCP, SOCK_STREAM, AF_INET });
	setup_connection(local_connections::broadcast, { IPPROTO_UDP, SOCK_DGRAM, AF_INET });
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Interface IP: " + hostname + ": " + connections[local_connections::local].address.get_as_string(), "Network Initalizer"));
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
		IPV4_Addr subnet_mask = get_subnet_mask(connections[local_connections::local].sock, connections[local_connections::local].address);
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