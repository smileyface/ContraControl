/*****************************************************************//**
 * \file   node_communication.h
 * \brief  
 * 
 * \author kason
 * \date   October 2021
 *********************************************************************/
#ifndef NETWORK_NODE_MESSAGES
#define NETWORK_NODE_MESSAGES
#include "messaging.h"

/** Node Messages utilities */
namespace node_messages
{
	/**
	 * Create a message container.
	 * 
	 * \param message type of message to create.
	 * \return created message.
	 */
	Network_Message network_message_factory(MESSAGES message);
	/**
	 * Using subsystem interfaces, populate the outgoing message.
	 * 
	 * \param message Message to format.
	 */
	void network_message_populate(Network_Message& message);
	/**
	 * Main communication brain. This will probably need to be split into Client tree and Server tree.
	 */
	void network_client_state_machine();
}
#endif
