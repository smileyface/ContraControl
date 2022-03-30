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
	 * |0-32  | 33-n |
	 * |ipv4  | name |
	 */
	class NODE_HELLO : public MESSAGE
	{
	public:
		NODE_HELLO() {};
		/**Constructor
		* \param in_addr The ip address of the node.
		* \param in_id The human readable name of the node.
		*/
		NODE_HELLO(unsigned char* in_addr, const char* in_id);

		std::vector<byte> pack();
		void unpack(std::vector<byte> packet);
		size_t size();

	private:
		byte addr[4]; ///<The ip address of the node
		Message_String id; ///<The name of the node

	};

	/**
	* Server acknowleging a client and requesting connection.
	* |           |      |
	* |:---------:|:----:|
	* |0          |  1-n |
	* |is_server  | name |
	*/
	class NODE_ACK : public MESSAGE
	{
	public:
		/**
		* Constructor
		* \param in_is_server Is the responding node a server.
		* \param in_id The human readable name of the node.
		*/
		NODE_ACK(bool in_is_server, const char* in_id);

		std::vector<byte> pack();
		void unpack(std::vector<byte> packet);
		size_t size();

	private:
		bool is_server;///<Is the responding node a server.
		Message_String id;///<Name of the responding node.
	};

	/** A future message added for test failures. Will be implemented by 0.0.6 */
	class NODE_CONNECT : public MESSAGE
	{
	public:
		NODE_CONNECT();
		std::vector<byte> pack();
		void unpack(std::vector<byte> packet);
		size_t size();
	private:
	};
}
#endif
