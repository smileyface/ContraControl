/*******************************************************************//**
 * \file   network_message_header.h
 * \brief  
 * 
 * \author kason
 * \date   April 2022
 *********************************************************************/

#ifndef NETWORK_MESSAGE_HEADER
#define NETWORK_MESSAGE_HEADER

#include "network_type.h"

/**
 * Header for message packets
 * |         |      |          |
 * |:-------:|:----:|:--------:|
 * |  01-08  |09-16 |   17-24  |
 * |pkt start|msg id|pkt length|
 */
struct Message_Header
{
	/** Beginning bit for the message */
	Byte message_start = 0x65;
	/** Which message is being sent */
	MESSAGES message_id = MESSAGES::UNDEFINED;
	/** How long the message is. Starts as the size of the header and footer. */
	Byte length = 6;

	/**
	* Boil the Message_Header down to an array of bytes that slapped at the beginning of a Network_Message and sent across the network.
	* It is mostly metadata about the message being sent.
	*
	* \return Byte array of the header.
	*/
	std::vector<Byte> pack();

	/**
	 * Expand the Message_Header to the object.
	 *
	 * \param byte_array_message Array of bytes to put in the objects.
	 */
	void unpack(std::vector<Byte> byte_array_message);
};

#endif // !NETWORK_MESSAGE_HEADER
