/*****************************************************************//**
 * \file   windows_network_interface.h
 * \brief  
 * 
 * \author kason
 * \date   October 2021
 *********************************************************************/
#ifdef _WIN32

#ifndef NETWORK_WINDOWS_INTERFACE
#define NETWORK_WINDOWS_INTERFACE
#include <vector>	//std::vector
#include <map>		//std::map

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "network_interface.h"
#include "types/connections.h"
extern struct addrinfo hints;
extern WORD wVersionRequested;

/**
 * Interface for a Windows system.
 */
class Windows_Network_Interface : public Network_Interface
{
public:
	Windows_Network_Interface();

	void setup_connection(Connection_Id connection_name, Socket_Maker maker);

	void initalize();
	void initalized();
	void clean_up();

	void send(Connection_Id node_id, char* message);
	char* listen(Connection_Id connection_name);


	
private:
	bool ipv4_compare(sockaddr_in* win_address, IPV4_Addr gen_address);
	IPV4_Addr convert_win_address(sockaddr_in* win_address);
	void setup_broadcast_socket(Connection& connect, IPV4_Addr host_ip);
	IPV4_Addr get_subnet_mask(SOCKET sock, IPV4_Addr host_ip);
	IPV4_Addr get_interface_address(std::string hostname, std::string interfaces);
	IPV4_Addr get_broadcast(IPV4_Addr host_ip, IPV4_Addr net_mask);
	NETWORK_ERRORS set_error_state(int err_code = -1);
};


#endif
#endif