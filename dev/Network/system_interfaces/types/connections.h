/******************************************************************//**
 * \file   connections.h
 * \brief  
 * 
 * \author kason
 * \date   March 2022
 *********************************************************************/

#ifndef NETWORK_CONNECTION_TYPE_H
#define NETWORK_CONNECTION_TYPE_H
#include <map>

#include "ipv4_addr.h"

#ifdef _WIN32
#include <WinSock2.h>
#endif // IS_WIN32
#ifdef __linux__
/** A rename for the file descriptor to the Windows SOCKET. This makes both systems work more similarly. */
typedef int SOCKET;
const int INVALID_SOCKET = 0;
#endif //__linux__

/**
 * A network connection container. To be paired with a Connection_Id for a full description of a connection to a remote node.
 */
struct Connection
{
	/** Socket to communicate through. Type is different for Windows v. Linux */
	SOCKET sock = INVALID_SOCKET;
	/** Address of the remote node. */
	ipv4_addr address = 0;
};

/** A handle for a connection to the remote node. Should correlate to \ref Node_Id. */
typedef std::string Connection_Id;
/** A map that pairs a Connection struct with a Connection_Id. */
typedef std::map<Connection_Id, Connection> Network_Connection_List;

namespace local_connections
{
	/** Connection to the Broadcast address */
	extern const Connection_Id broadcast;
	/** Connection to \ref model::my_node */
	extern const Connection_Id local;

	/**
	 * Setup inital local connection.
	 * \param list Reference to a nodes connection list.
	 */
	void setup(Network_Connection_List& list);

}


#endif // !NETWORK_CONNECTION_TYPE_H
