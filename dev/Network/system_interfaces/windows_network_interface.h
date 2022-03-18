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
	bool ipv4_compare(sockaddr_in* win_address, ipv4_addr gen_address);
	ipv4_addr convert_win_address(sockaddr_in* win_address);
	void setup_broadcast_socket(Connection& connect, ipv4_addr host_ip);
	ipv4_addr get_subnet_mask(SOCKET sock, ipv4_addr host_ip);
	ipv4_addr get_interface_address(std::string hostname, std::string interfaces);
	ipv4_addr get_broadcast(ipv4_addr host_ip, ipv4_addr net_mask);
	NETWORK_ERRORS set_error_state(int err_code = -1);
};


#endif
#endif