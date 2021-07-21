#include "../../../Utilities/Utilities/system.h"
#ifdef WIN32

#ifndef NETWORK_WINDOWS_INTERFACE
#define NETWORK_WINDOWS_INTERFACE
#include <stdio.h>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>
int ip_protocol = IPPROTO_TCP;
int sock_type = SOCK_STREAM;
class Windows_Network_Interface : public Network_Interface
{
public:
	Windows_Network_Interface();

	void connect(ipv4_addr addr);
	void initalize();
	bool initalized();
	
private:
	SOCKET ListenSocket = INVALID_SOCKET;
    char hostname[255];
    std::vector<ipv4_addr> local_ips;
};


#endif
#endif