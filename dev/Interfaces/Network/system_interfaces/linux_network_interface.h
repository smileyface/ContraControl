#include "../../../Utilities/Utilities/system.h"
#ifdef __linux__
#ifndef NETWORK_LINUNX_INTERFACE
#define NETWORK_LINUX_INTERFACE
#include <map>		//std::map

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "network_interface.h"

const int ip_protocol = IPPROTO_TCP;
const int sock_type = SOCK_STREAM;
const int sock_family = AF_INET;

class Linux_Network_Interface : public Network_Interface
{
	void connect_to_server(ipv4_addr addr);
	void scan_for_server();
	void initalized();
	void initalize();
	void clean_up();

	void server_start();
	void server_listen();

private:
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	bool server_running;
	std::map<ipv4_addr, int> accepted_connections;
};


#endif
#endif