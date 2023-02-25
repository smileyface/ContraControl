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
	~Linux_Network_Interface();
	void initalized();
	void initalize();
	void clean_up();
	void setup_connection(Connection_Id connection_name, Socket_Maker maker);


	void send(std::string node_id, char* message);
	char* listen(Connection_Id Connection_Id);

private:
	IPV4_Addr get_interface_addr();
	IPV4_Addr get_subnet_mask(SOCKET sock, IPV4_Addr host_ip);
	void setup_broadcast_socket(Connection& connect, IPV4_Addr host_ip);
	void setup_interface();
	bool server_running;
	struct ifaddrs* ifa;
};


#endif
#endif