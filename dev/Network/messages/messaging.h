/*****************************************************************//**
 * \file   messaging.h
 * \brief  
 * 
 * \author kason
 * \date   October 2021
 *********************************************************************/

#ifndef NETWORK_MESSAGES
#define NETWORK_MESSAGES

#include <cstring>
#include <vector>

typedef unsigned char byte;

/**
 * List of network messages
 */
enum class MESSAGES : byte
{
	/** See Node_Messages::NODE_HELLO */
	NODE_HELLO,
	/** See Node_Messages::NODE_ACK */
	NODE_ACK,
	NODE_GOODBYE,
	/** Undefined message. */
	UNDEFINED = 255
};

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
	byte message_start = 0x65; 
	/** Which message is being sent */
	MESSAGES message_id = MESSAGES::UNDEFINED; 
	/** How long the message is. Starts as the size of the header and footer. */
	byte length = 6; 
	std::vector<byte> pack();
};

extern byte crc_sum_Table[256];

void generate_crc_table();
/**
 * Footer for message packets
 * |          |          |
 * |:--------:|:--------:|
 * |  01-08   |  09-16   |
 * |checksum 1|checksum 2|
 */
struct MESSAGE_FOOTER 
{ 
	/** checksum bit 1 */
	byte chk1 = 0x00; 
	/** checksum bit 2 */
	byte chk2 = 0x00; 

	MESSAGE_FOOTER() {};
	MESSAGE_FOOTER(std::vector<byte> head_and_body);
	std::vector<byte> pack(std::vector<byte> head_and_body);

private:
};

/**
 * Base class for other messages.
 */
class MESSAGE 
{
public:
	virtual std::vector<byte> pack() = 0;
	virtual size_t size() = 0;
};

/**
 * A packed message waiting for sending
 * |         |       |         |
 * |:-------:|:-----:|:-------:|
 * |  01-24  | 25-n  | n+1-n+16|
 * |  Header |Message|  Footer |
 */
struct PACKED_MESSAGE
{

	PACKED_MESSAGE() {  };

	/**
	 * Constructor that sets a message up by accepting a MESSAGE type.
	 * @param message Message to be the main body of the message sent on the network.
	 */
	PACKED_MESSAGE(MESSAGE* message);
	std::vector<byte> get_packet();
private:
	/** Header */
	MESSAGE_HEADER header;
	/** Message to pack */
	MESSAGE* message = 0;
	/** Message as a packed string */
	std::vector<byte> packet;
	/** Footer, mainly checksums */
	MESSAGE_FOOTER footer;

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
	byte length;
	/** The string */
	char* str = 0;
	Message_String() { length = 0;}
	/**
	 * String creator
	 * @param string The string to be contained in the container.
	 */
	Message_String(const char* string)
	{
		length = sizeof(string)+1;
		str = (char*) string;
	}

	std::vector<byte> pack();
};

#endif // !NETWORK_MESSAGES