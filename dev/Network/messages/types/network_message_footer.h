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
struct MESSAGE_FOOTER
{
	/** checksum bit 1 */
	Byte chk1 = 0x00;
	/** checksum bit 2 */
	Byte chk2 = 0x00;

	MESSAGE_FOOTER() {};

	/**
	 * Generates the CRC footer from the rest of the message.
	 * \param head_and_body Byte array of the rest of the message combined in the proper order.
	 */
	MESSAGE_FOOTER(std::vector<Byte> head_and_body);
	/**
	 * Boil the MESSAGE_FOOTER down to an array of bytes that slapped at the end of a MESSAGE and sent across the network. It is mostly just a CRC sum
	 *
	 * \return Byte array of the footer.
	 */
	std::vector<Byte> pack();

	void unpack(std::vector<Byte>);


private:
};
