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

struct connection
{
	SOCKET sock = INVALID_SOCKET;
	ipv4_addr address = 0;
		
};

typedef std::string connection_id;
typedef std::map<connection_id, connection> network_connection_list;

namespace local_connections
{
	extern const connection_id broadcast;
	extern const connection_id local;

	void setup(network_connection_list& list);

}


#endif // !NETWORK_CONNECTION_TYPE_H
