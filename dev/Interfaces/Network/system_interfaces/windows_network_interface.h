#include "../../../Utilities/Utilities/system.h"
#ifdef _WIN32

#ifndef NETWORK_WINDOWS_INTERFACE
#define NETWORK_WINDOWS_INTERFACE
#include <vector>	//std::vector
#include <map>		//std::map

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "network_interface.h"
int ip_protocol = IPPROTO_TCP;
int sock_type = SOCK_STREAM;
int sock_family = AF_INET;
class Windows_Network_Interface : public Network_Interface
{
public:
	Windows_Network_Interface();

	void connect(ipv4_addr addr);
	void initalize();
	bool initalized();
	void clean_up();
	
	void server_start();
	
private:
	SOCKET ListenSocket = INVALID_SOCKET;
    char hostname[255];
    std::vector<ipv4_addr> local_ips;
	std::map<ipv4_addr, SOCKET> accepted_connections;
};


#endif
#endif