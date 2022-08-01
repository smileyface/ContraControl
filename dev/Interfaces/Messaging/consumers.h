/*****************************************************************//**
 * \file   consumers.h
 * \brief
 *
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef MESSAGE_CONSUMER_H
#define MESSAGE_CONSUMER_H

#include <vector>
#include "internal_messages.h"


 /**
  * An object for declaring that the containing object wants to be notified of a change, or recieve a message sent.
  */
struct Message_Consumer
{
	/**
	 * Set consumer up with a flag that determines if it's got a message available
	 * \param stale Reference to the message indicator flag.
	 * \param message_type Type of messages to be consumed.
	 */
	Message_Consumer(bool* stale, const Internal_Message* message_type);
	/**
	 * Notify the containing object that a message has been recieved.
	 */
	void notify();
	/**
	 * Remove notification. To be done after containing object has handled the message.
	 */
	void freshen();
	/**
	 * Is the message argument the correct type for this consumer
	 * \param message Internal_Message to check against.
	 * \return Is this message the correct type.
	 */
	bool correct_type(Internal_Message* message);

private:
	bool* stale = 0;
	const Internal_Message* message_type = 0;
};
/**
 * List of a message consumer. For use in message producers.
 */
typedef std::vector<Message_Consumer*> Consumer_List;
#endif
