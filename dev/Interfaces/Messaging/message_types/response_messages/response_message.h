/*****************************************************************//**
 * \file   response_message.h
 * \brief  
 * 
 * \author kason
 * \date   August 2022
 *********************************************************************/

#ifndef MESSAGE_RESPONSE_MESSAGE
#define MESSAGE_RESPONSE_MESSAGE

#include "../internal_message_type.h"

/**
 * A handle to get the responding message back.
 */
typedef int* Message_Receipt;

/**
 * A parent for responding to messages.
 */
class Response_Message : public Internal_Message
{
public:
	Response_Message();
	/**
	 * Checks if we are responding to the correct message.
	 * \param check_message Message to compare
	 * \return If the message is this message
	 * \todo Make this an overloaded ==
	 */
	virtual bool this_message(Message_Receipt check_message);

	/**
	 * \return The pointer to the recipt
	 */
	Message_Receipt get_receipt();
protected:
	Message_Receipt receipt; ///<An object to know which message we are responding to.
};

#endif

