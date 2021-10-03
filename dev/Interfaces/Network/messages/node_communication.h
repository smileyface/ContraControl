#include "messaging.h"

namespace Node_Messages
{
	/**
	 * Message letting the network know the local node has started.
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
}
