/*******************************************************************//**
 * \file   network_message_footer.h
 * \brief  
 * 
 * \author kason
 * \date   April 2022
 *********************************************************************/
#include "network_type.h"

/** A CRC table for fast checksum lookups. */
extern Byte crc_sum_Table[256];

/** Create a CRC table for fast checksum lookups. Populate crc_sum_Table */
void generate_crc_table();

/**
 * Footer for message packets
 * |          |          |
 * |:--------:|:--------:|
 * |  01-08   |  09-16   |
 * |checksum 1|checksum 2|
 */
struct Message_Footer
{
	/** checksum bit 1 */
	Byte chk1 = 0x00;
	/** checksum bit 2 */
	Byte chk2 = 0x00;

	Message_Footer() {};

	/**
	 * Generates the CRC footer from the rest of the message.
	 * \param head_and_body Byte array of the rest of the message combined in the proper order.
	 */
	Message_Footer(std::vector<Byte> head_and_body);
	/**
	 * Boil the Message_Footer down to an array of bytes that slapped at the end of a Network_Message and sent across the network. It is mostly just a CRC sum
	 *
	 * \return Byte array of the footer.
	 */
	std::vector<Byte> pack();

	/**
	 * Expand the Message_Footer to the 2 byte object. 
	 * 
	 * \param sum Array of bytes to put in the 2 byte objects.
	 */
	void unpack(std::vector<Byte> sum);


private:
};
