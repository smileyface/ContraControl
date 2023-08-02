/*****************************************************************//**
 * \file   network_interface.h
 * \brief
 *
 * \author kason
 * \date   October 2021
 *********************************************************************/
#ifndef NETWORK_SYSTEM_INTERFACE
#define NETWORK_SYSTEM_INTERFACE

#include "../messages.h"
#include "types/network_status_state.h"
#include "types/connections.h"

#include "Messaging/message_relay.h"

const unsigned short DEFAULT_PORT = 0xDCF5; ///<Port is 56565
const std::string INVALID_HOSTNAME = "INVALID"; ///<A marker for invalid hostnames

/** Protocol, type and family for a socket. */
struct Socket_Maker
{
	/** Protocol for socket connection. */
	int ip_protocol;
	/** Type of the socket. */
	int sock_type;
	/** Family of data. */
	int sock_family;
};
/**
 * \brief Interface for handling network communication between Nodes.
 *
 */
class Network_Interface
{
public:

	/**
	 * \brief Initalize the interface.
	 *
	 * Creates the socket.
	 */
	virtual void initalize() = 0;
	/**
	 * \brief Check if the interface is initalized.
	 *
	 * If the interface is not initalized, this sets the status_state as an error.
	 * If it is initalized, it sets the state as NETWORK_STATUS::NETWORK_INITALIZED.
	 */
	virtual void initalized() = 0;
	/**
	 * \brief Close all interface objects.
	 */
	virtual void clean_up() = 0;

	//getters
	/**
	 * \brief Get the status_state
	 *
	 * \return Network_Status_State
	 */
	Network_Status_State get_status();
	/**
	 * \brief Is the network a server.
	 * 
	 * \return The Interface is in the server state
	 */
	bool server();
	/**
	 * \brief Is the network a client.
	 * 
	 * \return The Interface is in the client state
	 */
	bool client();

	//setters
	/**
	* \brief Set the Node as server.
	*/
	void set_server();
	/**
	 * \brief Set the Node as client.
	 */
	void set_client();
	/**
	 * Set the hostname manually.
	 *
	 * \param hostname Name to set.
	 */
	void set_hostname(const std::string& hostname);
	/**
	 * \brief setup a connection, either local or remote.
	 *
	 * \param connection_id Node to connect to.
	 * \param maker Setup parameters.
	 */
	virtual void setup_connection(Connection_Id connection_id, Socket_Maker maker) = 0;

	//Communication Code
	/**
	 * Send a message to a node.
	 *
	 * \param connection_id Node to send message to.
	 * \param message Array of bytes to send to Node.
	 */
	virtual void send(Connection_Id connection_id, char* message) = 0;
	/**
	 * Listen to a specific connection.
	 *
	 * \param connection_id Node to listen to messages from.
	 * \return Message as array of bytes.
	 */
	virtual char* listen(Connection_Id connection_id) = 0;
	/**
	 * \brief Setup network interface as a given interface.
	 * \param i Given interface.
	 */
	void set_interface(const std::string& i);

	/**
	 * \brief Set status of the interface.
	 * \param status Status to set the interface state to.
	 */
	void set_network_state(NETWORK_STATUS status);

	/**
	 * \param connection Name of the desired connection.
	 * \return Desired Connection.
	 */
	Connection get_connection(Connection_Id connection);

	/**
	 * \return Hostname of local.
	 */
	std::string get_hostname();

	//Constants
	/**
	 * \brief localhost address
	 */
	const IPV4_Addr localhost = IPV4_Addr("127.0.0.1");
protected:
	/**
	 * \brief Is the local node a server.
	 */
	bool is_server = true;
	/**
	 * \brief the interface name of the local node.
	 */
	std::string hostname;
	/**
	 * \brief State of the network interface.
	 */
	Network_Status_State status_state;
	/**
	 * Which interface are we using
	*/
	std::string interfaces;
	/**
	 * Map of known connections
	 */
	Network_Connection_List connections;
};

#endif