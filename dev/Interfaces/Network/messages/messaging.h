/*******************************************************************
 * \file   messaging.h
 * \brief  
 * 
 * \author kason
 * \date   September 2021
 *********************************************************************/

#ifndef NETWORK_MESSAGES
#define NETWORK_MESSAGES

#include <cstring>

enum class MESSAGES : char
{
	NODE_HELLO,
	NODE_GOODBYE,
	UNDEFINED
};


/**
 * Header for message packets
 * |         |      |          |
 * |:-------:|:----:|:--------:|
 * |   01    |  02  |    03    |
 * |pkt start|msg id|pkt length|
 */
struct MESSAGE_HEADER 
{ 
	/** Beginning bit for the message */
	char message_start = 0x65; 
	/** Which message is being sent */
	MESSAGES message_id = MESSAGES::UNDEFINED; 
	/** How long the message is. Starts as the size of the header and footer. */
	unsigned short length = 6; 
};
/**
 * Footer for message packets
 * |          |          |
 * |:--------:|:--------:|
 * |   01     |    02    |
 * |checksum 1|checksum 2|
 */
struct MESSAGE_FOOTER 
{ 
	/** checksum bit 1 */
	char chk1 = 0x00; 
	/** checksum bit 2 */
	char chk2 = 0x00; 
};
/**
 * Base class for other messages.
 */
struct MESSAGE { };
/**
 * A packed message waiting for sending
 * |         |       |         |
 * |:-------:|:-----:|:-------:|
 * |  01-06  | 07-n  | n+1-n+3 |
 * |  Header |Message|  Footer |
 */
struct PACKED_MESSAGE
{
	/** Header */
	MESSAGE_HEADER header;
	/** Message body */
	MESSAGE* message = 0;
	/** Footer, mainly checksums */
	MESSAGE_FOOTER footer;
	PACKED_MESSAGE() {};
	/**
	 * Constructor that sets a message up by accepting a MESSAGE type.
	 * @param message Message to be the main body of the message sent on the network.
	 */
	PACKED_MESSAGE(MESSAGE* message);
	/**
	 * Get MESSAGES based on byte 2 of the header.
	 * @return The message type of the main body.
	 */
	MESSAGES get_message_enum_by_type();

};

/**
 * A container for adding strings to network messages.
 */
struct Message_String
{
	/** Length of the string */
	unsigned short length;
	/** The string */
	char* str;
	Message_String() { length = 0; str[0] = '\0'; }
	/**
	 * String creator
	 * @param string The string to be contained in the container.
	 */
	Message_String(const char* string)
	{
		length = sizeof(string);
		std::memcpy(str, string, sizeof(length));
	}
};

/** Create an array of bytes to be put in a network buffer based on a PACKED_MESSAGE. */
unsigned char* pack();


#endif // !NETWORK_MESSAGES