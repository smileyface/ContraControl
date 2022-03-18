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

	void setup_connection(std::string connection_name, socket_maker maker);

	void connect_to_server(ipv4_addr addr);
	void scan_for_server();
	void initalize();
	void initalized();
	void clean_up();
	
	void server_start();

	void send(std::string node_id, char* message);

	static bool ipv4_compare(sockaddr_in* win_address, ipv4_addr gen_address)
	{
		return win_address->sin_addr.S_un.S_addr == gen_address.S_un.S_addr;
	}
	static ipv4_addr convert_win_address(sockaddr_in* win_address)
	{
		ipv4_addr gen_addr;
		gen_addr.S_un.S_addr = win_address->sin_addr.S_un.S_addr;
		return gen_addr;
	}
	
private:
};


#endif
#endif