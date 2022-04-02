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

ipv4_addr Windows_Network_Interface::get_broadcast(ipv4_addr host_ip, ipv4_addr net_mask)
{
	return host_ip.S_un.S_addr | ~net_mask.S_un.S_addr;
}
ipv4_addr Windows_Network_Interface::get_interface_address(std::string hostname, std::string interfaces)
{
    /* Declare and initialize variables */

    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    unsigned int i = 0;

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
	PMIB_IPADDRTABLE pIPAddrTable;
	MIB_IPADDRROW found_ip = MIB_IPADDRROW();

    struct sockaddr_in* sockaddr_ipv4 = 0;
    // Allocate a 15 KB buffer to start with.
    outBufLen = WORKING_BUFFER_SIZE;

    pAddresses = (IP_ADAPTER_ADDRESSES*)MALLOC(outBufLen);
	pIPAddrTable = (MIB_IPADDRTABLE*)MALLOC(sizeof(MIB_IPADDRTABLE));
    if (pAddresses == NULL) {
        printf
        ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
        exit(1);
    }

	if (pIPAddrTable) {
		// Make an initial call to GetIpAddrTable to get the
		// necessary size into the dwSize variable
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) ==
			ERROR_INSUFFICIENT_BUFFER) {
			FREE(pIPAddrTable);
			pIPAddrTable = (MIB_IPADDRTABLE*)MALLOC(dwSize);

		}
		if (pIPAddrTable == NULL) {
			status_state.set_error(NETWORK_ERRORS::UNINITALIZED_INTERFACE);
			network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, "Unable to get IP Address Table", "Getting IP Addr Table"));
			throw NetworkErrorException();
		}
	}

	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR) {
		printf("GetIpAddrTable failed with error %d\n", dwRetVal);
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),       // Default language
			(LPTSTR)&lpMsgBuf, 0, NULL)) {
			status_state.set_error(NETWORK_ERRORS::UNKNOWN_ERROR);
			network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, (LPTSTR)lpMsgBuf, "Getting IP Addr Table"));
			LocalFree(lpMsgBuf);
		}
	}

	if ((int)pIPAddrTable->dwNumEntries == 1)
	{
		found_ip = pIPAddrTable->table[0];
	}
	else if ((int)pIPAddrTable->dwNumEntries == 2 && pIPAddrTable->table[1].dwAddr == ipv4_addr("127.0.0.1").S_un.S_addr)
	{
		found_ip = pIPAddrTable->table[0];
	}
	
    dwRetVal =
        GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);


    if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
        FREE(pAddresses);
        pAddresses = NULL;
    }

	for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses; pCurrAddresses = pCurrAddresses->Next)
	{
		IN_ADDR IPAddr{};
		if (found_ip.dwAddr != MAXDWORD && pCurrAddresses->FriendlyName == a)
		{
			std::wstring thing(pCurrAddresses->FriendlyName);
			std::string friend_name = std::string(thing.begin(), thing.end());
			IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[i].dwAddr;
			char str[INET_ADDRSTRLEN];
			// now get it back and print it
			inet_ntop(AF_INET, &(IPAddr), str, INET_ADDRSTRLEN);
			std::string message = friend_name + ": " + str;
			network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, message, "Local interface connection"));
		}
	}
    if (pAddresses) 
    {
        FREE(pAddresses);
    }
	if (pIPAddrTable) {
		FREE(pIPAddrTable);
		pIPAddrTable = NULL;
	}
    return ipv4_addr(found_ip.dwAddr);
}

ipv4_addr Windows_Network_Interface::get_subnet_mask(SOCKET sock, ipv4_addr host_ip)
{
	INTERFACE_INFO InterfaceList[20] = { 0 };
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
	network::network_message_interface->push(System_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, "Subnet Mask: " + subnet_mask.get_as_string(), "Subnet Mask Finder"));
	return subnet_mask;
}

void Windows_Network_Interface::setup_broadcast_socket(Connection& connect, ipv4_addr host_ip)
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

	interfaces = "Ethernet";
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