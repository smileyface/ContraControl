/*****************************************************************//**
 * \file   network_main.h
 * \brief  
 * 
 * \author kason
 * \date   March 2022
 *********************************************************************/
#include "system_interfaces/network_interface.h"
#include "Threading/threading.h"
/**
 * \brief Main network interface. Use this instead of creating a new Network_Interface object.
 *
 */
namespace network
{
    extern Network_Interface* network_interface; ///<Main interface object.
     /**
     * .The string of the namespace name. This is for locating Messages.
     */
    static const char* subsystem_name = "Network";	
    /**
     * Task to add the network to the scheduler.
     */
    extern Task network_task;
    /**
     * Is the network running
     */
    extern bool network_running;

    /**
     * \brief Setup network interface as a system specific interface.
     */
    extern void initalize();

    /**
    * \brief Setup network interface as a given interface.
    * \param interfaces Given interface.
    */
    extern void initalize(std::string interfaces);

    /**
     * \brief Intantiate a system specific interface.
     */
    extern void instantiate_interface();

    /**
     * \brief Teardown and clean up system specific network interface.
     */
    extern void clean_up();
    /**
     * \brief Send a message on the network interface.
     *
     * \param dest Node to send this message to.
     * \param mesg Message to send
     */
    extern void send_message(Connection_Id dest, Network_Message mesg);

    /**
     * \brief Listen for a specific message. 
     * 
     * \todo make this use the network recieve buffer.
     * \param src The connection that will be sending this message.
     * \param listen_for Message to watch out for.
     * \return Message when heard
     */
    extern Network_Message listen_for_message(Connection_Id src, MESSAGES listen_for);

    /**
     * \brief Start interface as a server.
     */
    extern void start_server();
    /**
     * \brief Start interface as a client.
     */
    extern void start_client();
    /**
     * \brief Set interface from external source.
     * \param i Interface to set as source.
     */
    extern void set_interface(std::string i);

};