#ifndef NETWORK_MESSAGE_HEADER
#define NETWORK_MESSAGE_HEADER

#include "network_type.h"
#include "messages.h"

/**
 * Header for message packets
 * |         |      |          |
 * |:-------:|:----:|:--------:|
 * |  01-08  |09-16 |   17-24  |
 * |pkt start|msg id|pkt length|
 */
struct MESSAGE_HEADER
{
	/** Beginning bit for the message */
	Byte message_start = 0x65;
	/** Which message is being sent */
	MESSAGES message_id = MESSAGES::UNDEFINED;
	/** How long the message is. Starts as the size of the header and footer. */
	Byte length = 6;

	/**
	* Boil the MESSAGE_HEADER down to an array of bytes that slapped at the beginning of a MESSAGE and sent across the network.
	* It is mostly metadata about the message being sent.
	*
	* \return Byte array of the header.
	*/
	std::vector<Byte> pack();

	void unpack(std::vector<Byte> byte_array_message);
};

#endif // !NETWORK_MESSAGE_HEADER
