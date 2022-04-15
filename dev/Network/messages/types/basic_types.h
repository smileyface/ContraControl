/*******************************************************************//**
 * \file   basic_types.h
 * \brief  
 * 
 * \author kason
 * \date   April 2022
 *********************************************************************/

#ifndef NETWORK_MESSAGE_BASIC_TYPES
#define NETWORK_MESSAGE_BASIC_TYPES

#include "network_type.h"


/** A byte to send over the network. */
class Network_Byte : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(Byte);
	/**
    * Return a Byte.
	* \return data.
	*/
	Byte get_data();
private:
	Byte number;
};

/** A word to send over the network. This value can be negative. */
class Network_Word : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(int);
	/**
	* Return a Byte.
	* \return data.
	*/
	short get_data();
private:
	short number;
};

/** A percentage to send over the network. There is an integer and a decimal. */
class Network_Percent : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(float);
	/**
	 * Return a float.
	* \return data.
	*/
	float get_data();
private:
	Byte integer;
	Byte decimal;
};

/** A string to send over the network. There is a byte for size and then that many bytes following. */
class Network_String : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(std::string);
	/**
	 * Return a pair of Byte and a string.
	 * \return data.
	 */
	std::pair<Byte, std::string> get_data();
private:
	unsigned char length;
	std::string message;
};

/** A boolean to send over the network. This is a byte to save work with bit shifting. */
class Network_Bool : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(bool);
	/**
	* Return a boolean.
	* \return data.
	*/
	bool get_data();
private:
	Byte boolean;
};

/** An IPV4 address to send over the network. It's a series of 4 bytes. */
class Network_Address : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(IPV4_Addr);
	/**
	 * Return the address.
	 * \return data.
	 */
	IPV4_Addr get_data();
private:
	IPV4_Addr address;
};

#endif
