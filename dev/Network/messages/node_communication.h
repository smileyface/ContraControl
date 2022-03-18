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

namespace Node_Messages
{
	/**
	 * Message letting the network know a client has entered the network.
	 * |      |      |
	 * |:----:|:----:|
	 * |0-16  | 17-n |
	 * |ipv4  | name |
	 */
	struct NODE_HELLO : MESSAGE
	{
		unsigned char addr[4]; ///<The ip address of the node
		Message_String id; ///<The name of the node
		/**
		 * Constructor
		 * \param in_addr The ip address of the node.
		 * \param in_id The human readable name of the node.
		 */
		NODE_HELLO(unsigned char* in_addr, const char* in_id);
	};

	struct NODE_ACK : MESSAGE
	{
		Message_String id;
		int alias_int;
	};
}
#endif
