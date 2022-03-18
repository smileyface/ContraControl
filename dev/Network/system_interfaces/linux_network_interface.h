/*****************************************************************//**
 * \file   linux_network_interface.h
 * \brief  
 * 
 * \author kason
 * \date   October 2021
 *********************************************************************/

#ifdef __linux__
#ifndef NETWORK_LINUNX_INTERFACE
#define NETWORK_LINUX_INTERFACE
#include <map>		//std::map

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>	    //std::vector

#include "network_interface.h"
//COMMON TYPEDEFS

typedef unsigned long DWORD;
const unsigned long ERROR_NOT_FOUND = 1168L;

class Linux_Network_Interface : public Network_Interface
{
public:
	Linux_Network_Interface();
	void initalized();
	void initalize();
	void clean_up();
	void setup_connection(connection_id connection_name, socket_maker maker);


	void send(std::string node_id, char* message);
	char* listen(connection_id connection_id);

	void set_my_ip();

private:
	ipv4_addr get_interface_addr();
	ipv4_addr get_subnet_mask(SOCKET sock, ipv4_addr host_ip);
	void setup_broadcast_socket(connection& connect, ipv4_addr host_ip);
	bool server_running;
};


#endif
#endif