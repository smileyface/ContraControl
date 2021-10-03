#ifndef NETWORK_SYSTEM_INTERFACE
#define NETWORK_SYSTEM_INTERFACE

#include <string>
#include "Network/messages.h"
#include "types/ipv4_addr.h"
#include "types/network_status_state.h"

const unsigned short DEFAULT_PORT = 0xDCF5;
const std::string invalid_hostname = "INVALID";

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
     * 
     * \return This should not return anything, but Doxygen thinks it does.
     */
    virtual void initalize() = 0;
    /**
     * \brief Check if the interface is initalized.
     * 
     * If the interface is not initalized, this sets the status_state as an error. 
     * If it is initalized, it sets the state as NETWORK_STATUS::NETWORK_INITALIZED.
     * \return This should not return anything, but Doxygen thinks it does.
     */
    virtual void initalized() = 0;
    /**
     * \brief Close all interface objects
     * \return This should not return anything, but Doxygen thinks it does.
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
     * \brief Return the IP of the local node
     * 
     * \return ipv4 as 4 unsigned chars
     */
    unsigned char* local_ip();

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
     * \brief Set the my ip object. Does it from the ipconfig/ifconfig
     *
     * \return This should not return anything, but Doxygen thinks it does.
     */
    virtual void set_my_ip() = 0;

    //Client Code
    /**
     * \brief Connect to a server.
     * 
     * \param addr Address of server.
     * \return This should not return anything, but Doxygen thinks it does.
     */
    virtual void connect_to_server(ipv4_addr addr) = 0;
    /**
     * \brief Scan for a server to connect to.
     * 
     * \todo Do this through broadcast instead of an ARP blast.
     * \return This should not return anything, but Doxygen thinks it does.
     */
    virtual void scan_for_server() = 0;
    
    //Server Code
    /**
     * \brief Start the server in a thread
     * \return This should not return anything, but Doxygen thinks it does.
     */
    virtual void server_start() = 0;

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
     * \brief The local node ip address.
     */
    ipv4_addr my_ip = ipv4_addr("255.255.255.255");
    /**
     * \brief the interface name of the local node.
     */
    std::string hostname;
    /**
     * \brief State of the network interface.
     */
    Network_Status_State status_state;
};

namespace network
{
    extern Network_Interface* network_interface;

    extern void init_network_interfaces();
    extern void teardown_network_interfaces();
    extern void send_message(MESSAGE*);

    extern void start_server();
    extern void start_client();
}

#endif