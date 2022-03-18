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

#include "Messaging/system_messaging.h"

const unsigned short DEFAULT_PORT = 0xDCF5; ///<Port is 56565
const std::string invalid_hostname = "INVALID"; ///<A marker for invalid hostnames

struct socket_maker
{
    int ip_protocol;
    int sock_type;
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

    //setters
    /**
    * \brief Set the Node as server.
    */
    void set_server();
    /**
     * \brief Set the Node as client.
     */
    void set_client();
    void set_hostname(std::string hostname);
    /**
     * \brief Set the my ip object. Does it from the ipconfig/ifconfig
     */
    virtual void setup_connection(std::string connection_name, socket_maker maker) = 0;

    //Client Code
    /**
     * \brief Connect to a server.
     * 
     * \param addr Address of server.
     */
    virtual void connect_to_server(ipv4_addr addr) = 0;
    /**
     * \brief Scan for a server to connect to.
     * 
     * \todo Do this through broadcast instead of an ARP blast.
     */
    virtual void scan_for_server() = 0;
    
    //Server Code
    /**
     * \brief Start the server in a thread
     */
    virtual void server_start() = 0;

    //Communication Code
    virtual void send(std::string node_id, char* message) = 0;
   //Constants
   /**
    * \brief localhost address
    */
    const ipv4_addr localhost = ipv4_addr("127.0.0.1");
protected:
    /**
     * \brief Is the local node a server.
     */
    bool is_server = false;
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
    network_connection_list connections;
};

#endif