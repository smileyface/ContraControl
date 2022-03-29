/*****************************************************************//**
 * \file   system_messaging.h
 * \brief
 *
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef SYSTEM_MESSAGE_INTERFACE_H
#define SYSTEM_MESSAGE_INTERFACE_H

#include <string>

#include "Messaging/consumers.h"

/**
 Level of the message.
 */
enum class MESSAGE_PRIORITY {
	/**
	Debug message. For very verbose logging.
	*/
	DEBUG_MESSAGE,
	/**
	Informational message. For verbose logging.
	*/
	INFO_MESSAGE,
	/**
	A non-program stopping error.
	*/
	ERROR_MESSAGE,
	/**
	A program breaking error.
	*/
	SEVERE_MESSAGE

};

/**
 * Return message priority as a string.
 * \param al Priority of the message.
 * \return Message Priority as a standard string.
 */
std::string message_priority_as_string(MESSAGE_PRIORITY al);


/**
 * System level messsages
 */
struct System_Message
{
	/**
	 * How dire this message is.
	 */
	MESSAGE_PRIORITY priority;
	/**
	 * Message to be sent.
	 */
	std::string message;
	/**
	 * Where this message is from.
	 */
	std::string location;
	/** Is this message valid. Invalid messages are not sent. */
	bool valid_message;
	/**
	 * Create a new message with defined priority, message, and location. 
	 * 
	 * This is the standard way of creating a message. 
	 * Message validity is set to true.
	 * \param pri Priority of the message
	 * \param msg Message to be sent
	 * \param loc Sender of this message
	 */
	System_Message(MESSAGE_PRIORITY pri, std::string msg, std::string loc);
	/**
	 * Create an empty message with a defined validity.
	 * \param valid_message Desired validity to set message to.
	 */
	System_Message(bool valid_message);
};

/**
 * Message relay system as a singleton.
 * 
 * \todo rename to Message_Relay
 */
class System_Messages
{
public:
	/**
	 * Push a message to the Message Relay.
	 * 
	 * \param message Message to add to the relay
	 */
	void push(System_Message message);
	/**
	 * Get the first message from the Message Relay for a Message Consumer.
	 * 
	 * \param mc Pointer to the consumer requesting to get its messages.
	 * \return first message on the relay for the requesting Consumer.
	 */
	System_Message pop(Message_Consumer* mc);
	/**
	 * Get instance of the singleton.
	 * \return Instance of the message relay.
	 */
	static System_Messages* get_instance();
	/**
	 * Register consumer for message consumption.
	 * \param mc Add a Message_Consumer to the list of known consumers. You must do this before you are able to recieve messages.
	 */
	void register_consumer(Message_Consumer* mc);

	void deregister_consumer(Message_Consumer* mc);
private:
	System_Messages();
	std::vector<std::pair<System_Message, Consumer_List>> list_of_message;
	std::vector<Message_Consumer*> list_of_registered_consumers;
	static System_Messages* instance;

};

#endif // !SYSTEM_MESSAGE_INTERFACE_H


