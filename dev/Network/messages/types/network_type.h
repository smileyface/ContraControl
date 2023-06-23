/*******************************************************************//**
 * \file   network_type.h
 * \brief  
 * 
 * \author kason
 * \date   April 2022
 *********************************************************************/

#ifndef NETWORK_MESSAGE_BASE_TYPE
#define NETWORK_MESSAGE_BASE_TYPE

#include <vector>

#include "../../system_interfaces/types/ipv4_addr.h"

/** An unsigned char that can be sent over the network */
typedef unsigned char Byte;
/** An array of bytes */
typedef std::vector<Byte> Byte_Array;

/**
 * Base type for a wrapper for data to be sent over the network. It provides packing/unpacking instructions for the type as well as a sizing information.
 */
class Network_Messaging_Type
{
public:
	/**
	 * \return Size of type in bytes.
	 */
	virtual Byte size() = 0;
	/**
	 * \return The type in vector of bytes.
	 */
	virtual Byte_Array pack() = 0;
	/**
	 * Converts vector of bytes to type.
	 * \param array vector of bytes.
	 */
	virtual void unpack(Byte_Array& array) = 0;

	/**
	 * Set data to i.
	 * \param i value to set data to.
	 */
	virtual void operator=(IPV4_Addr i);
	/**
	 * Set data to i.
	 * \param i value to set data to.
	 */
	virtual void operator=(bool i);
	/**
	 * Set data to i.
	 * \param i value to set data to.
	 */
	virtual void operator=(std::string i);
	/**
	 * Set data to i.
	 * \param i value to set data to.
	 */
	virtual void operator=(float i);
	/**
	 * Set data to i.
	 * \param i value to set data to.
	 */
	virtual void operator=(int i);
	/**
	 * Set data to i.
	 * \param i value to set data to.
	 */
	virtual void operator=(Byte i);
};

#endif
