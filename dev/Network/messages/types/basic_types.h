/*********************************************************************
 * \file   basic_types.h
 * \brief  
 * 
 * \author kason
 * \date   April 2022
 *********************************************************************/

#ifndef NETWORK_MESSAGE_BASIC_TYPES
#define NETWORK_MESSAGE_BASIC_TYPES
#include <string>

#include "network_type.h"


/** A byte to send over the network. */
class Network_Byte : public Network_Messaging_Type
{
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(Byte);
private:
	Byte number;
};

/** A word to send over the network. This value can be negative. */
class Network_Word : public Network_Messaging_Type
{
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(int);
private:
	short number;
};

/** A percentage to send over the network. There is an integer and a decimal. */
class Network_Percent : public Network_Messaging_Type
{
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(float);
private:
	Byte integer;
	Byte decimal;
};

class Network_String : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(std::string);
	std::pair<Byte, std::string> get_data();
private:
	unsigned char length;
	std::string message;
};

class Network_Bool : public Network_Messaging_Type
{
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(bool);
private:
	unsigned char boolean;
};

class Network_Address : public Network_Messaging_Type
{
public:
	Byte size();
	Byte_Array pack();
	void unpack(Byte_Array&);
	void operator=(ipv4_addr);
	
	ipv4_addr get_data();
private:
	ipv4_addr address;
};

#endif
