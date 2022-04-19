/*******************************************************************//**
 * \file   messages.h
 * \brief  
 * 
 * \author kason
 * \date   April 2022
 *********************************************************************/

#ifndef NETWORK_MESSAGES_ENUM_TYPE
#define NETWORK_MESSAGES_ENUM_TYPE

#include "network_type.h"
 /**
  * List of network messages
  */
enum class MESSAGES : Byte
{
	/** See Node_Messages::NODE_HELLO */
	NODE_HELLO,
	/** See Node_Messages::NODE_ACK */
	NODE_ACK,
	/** See Node_Messages::NODE_GOODBYE */
	NODE_GOODBYE,
	/** Undefined message. */
	UNDEFINED = 255
};

/**
 * Get MESSAGES enum value in a human readable form.
 * \param type MESSAGES value to convert to human readable.
 * \return Human readable.
 */
std::string get_message_type_string(MESSAGES type);


#endif // !NETWORK_MESSAGES_ENUM_TYPE

