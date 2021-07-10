#include "../../../Utilities/Utilities/system.h"
#ifdef IS_UNIX
#ifndef NETWORK_LINUNX_INTERFACE
#define NETWORK_LINUX_INTERFACE

#include <sys/socket.h>

#include "network_interface.h"

class Linux_Network_Interface : public Network_Interface
{

	void connect(ipv4_addr addr) {};
};


#endif
#endif