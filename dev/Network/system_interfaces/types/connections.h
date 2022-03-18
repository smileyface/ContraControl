#ifndef NETWORK_CONNECTION_TYPE_H
#define NETWORK_CONNECTION_TYPE_H
#include <map>
#include <string>

#include "ipv4_addr.h"

#ifdef _WIN32
#include <WinSock2.h>
#endif // IS_WIN32
#ifdef __linux__
typedef int SOCKET;
const int INVALID_SOCKET = 0;
#endif //__linux__

struct Connection
{
	SOCKET sock = INVALID_SOCKET;
	ipv4_addr address = 0;
		
};

typedef std::string Connection_Id;
typedef std::map<Connection_Id, Connection> Network_Connection_List;

namespace local_connections
{
	extern const Connection_Id broadcast;
	extern const Connection_Id local;

	void setup(Network_Connection_List& list);

}


#endif // !NETWORK_CONNECTION_TYPE_H
