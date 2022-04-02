/*********************************************************************
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

typedef unsigned char Byte;
typedef std::vector<Byte> Byte_Array;

class Network_Messaging_Type
{
public:
	virtual Byte size() = 0;
	virtual Byte_Array pack() = 0;
	virtual void unpack(Byte_Array&) = 0;

	virtual void operator=(ipv4_addr);
	virtual void operator=(bool);
	virtual void operator=(std::string);
	virtual void operator=(float);
	virtual void operator=(int);
	virtual void operator=(Byte);
};

#endif
