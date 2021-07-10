#include "../../../Utilities/Utilities/system.h"
#ifdef IS_WIN32

#ifndef NETWORK_WINDOWS_INTERFACE
#define NETWORK_WINDOWS_INTERFACE
#include <stdio.h>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>
class Windows_Network_Interface : public Network_Interface
{
public:
	Windows_Network_Interface()
	{
        WORD wVersionRequested = MAKEWORD(1, 1);
        WSADATA wsaData;
        PHOSTENT hostinfo;
        char* ip;

        if (WSAStartup(wVersionRequested, &wsaData) != 0)
            throw -1;
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
	}
	void connect(ipv4_addr addr);

	
private:
	SOCKET ListenSocket;
    char hostname[255];
    std::vector<ipv4_addr> local_ips;
};


#endif
#endif