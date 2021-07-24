#include "../../../Utilities/Utilities/system.h"
#ifdef __linux__
#ifndef NETWORK_LINUNX_INTERFACE
#define NETWORK_LINUX_INTERFACE

#include <sys/socket.h>

#include "network_interface.h"

class Linux_Network_Interface : public Network_Interface
{

	void connect(ipv4_addr addr);
	bool initalized();
	void initalize();
	void clean_up();

	void listen();
};


#endif
#endif