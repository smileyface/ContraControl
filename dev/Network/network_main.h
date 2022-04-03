/*****************************************************************//**
 * \file   network_main.h
 * \brief  
 * 
 * \author kason
 * \date   March 2022
 *********************************************************************/
#include "system_interfaces/network_interface.h"
/**
 * \brief Main network interface. Use this instead of creating a new Network_Interface object.
 *
 */
namespace network
{
    extern Network_Interface* network_interface; ///<Main interface object.
    /**
    * Message system
    */
    extern System_Messages* network_message_interface;

    /**
     * \brief Setup network interface as a system specific interface.
     */
    extern void init_network_interfaces();

    extern void init_network_interfaces(std::string interfaces);
    /**
     * \brief Teardown and clean up system specific network interface.
     */
    extern void teardown_network_interfaces();
    /**
     * \brief Send a message on the network interface.
     *
     * \param mesg Message to send
     */
    extern void send_message(MESSAGE* mesg);

    /**
     * \brief Start interface as a server.
     */
    extern void start_server();
    /**
     * \brief Start interface as a client.
     */
    extern void start_client();

    extern void set_interface(std::string i);

};