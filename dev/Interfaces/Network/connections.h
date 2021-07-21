#ifndef NETWORK_CONNECTIONS
#define NETWORK_CONNECTIONS

#include "system_interfaces/network_interface.h"

struct Connection
{
	ipv4_addr address;
	int port = 656565;
};

typedef std::vector<Connection> Connection_List;
#endif // !NETWORK_CONNECTIONS
