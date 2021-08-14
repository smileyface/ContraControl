#include "../../../Utilities/Utilities/system.h"
#ifdef _WIN32

#ifndef NETWORK_WINDOWS_INTERFACE
#define NETWORK_WINDOWS_INTERFACE
#include <vector>	//std::vector
#include <map>		//std::map

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "network_interface.h"
const int ip_protocol = IPPROTO_TCP;
const int sock_type = SOCK_STREAM;
const int sock_family = AF_INET;
class Windows_Network_Interface : public Network_Interface
{
public:
	Windows_Network_Interface();

	void connect_to_server(ipv4_addr addr);
	void scan_for_server();
	void initalize();
	bool initalized();
	void clean_up();
	
	void server_start();

	static bool ipv4_compare(sockaddr_in* win_address, ipv4_addr gen_address)
	{
		return win_address->sin_addr.S_un.S_addr == gen_address.S_un.S_addr;
	}
	static ipv4_addr convert_win_address(sockaddr_in* win_address)
	{
		ipv4_addr gen_addr;
		gen_addr.S_un.S_addr = win_address->sin_addr.S_un.S_addr;
		return gen_addr;
	}
	
private:
	SOCKET sock = INVALID_SOCKET;
    std::vector<ipv4_addr> local_ips;
	std::map<ipv4_addr, SOCKET> accepted_connections;
};


#endif
#endif