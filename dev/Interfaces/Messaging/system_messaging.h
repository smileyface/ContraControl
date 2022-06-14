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
 //Messaging types
#include "Messaging/message_types/internal_message_type.h"
#include "Messaging/message_types/logging_message.h"

/**
 * Message relay system as a singleton.
 *
 * \todo rename to Message_Relay
 */
class Message_Relay
{
public:
	/**
	 * Push a message to the Message Relay.
	 *
	 * \param message Message to add to the relay
	 */
	void push(Internal_Message* message);
	/**
	 * Get the first message from the Message Relay for a Message Consumer.
	 *
	 * \param mc Pointer to the consumer requesting to get its messages.
	 * \return first message on the relay for the requesting Consumer.
	 */
	Internal_Message* pop(Message_Consumer* mc);
	/**
	 * Get instance of the singleton.
	 * \return Instance of the message relay.
	 */
	static Message_Relay* get_instance();
	/**
	 * Register consumer for message consumption.
	 * \param mc Add a Message_Consumer to the list of known consumers. You must do this before you are able to recieve messages.
	 */
	void register_consumer(Message_Consumer* mc);

	/**
	 * Remove consumer from the consumer list. The system that owns this consumer will not be able to recieve messages while deregistered.
	 * Any messages sent while not registered will just be missed.
	 * \param mc Consumer to be removed from the list.
	 */
	void deregister_consumer(Message_Consumer* mc);
private:
	Message_Relay();
	std::vector<std::pair<Internal_Message*, Consumer_List>> list_of_message;
	std::vector<Message_Consumer*> list_of_registered_consumers;
	static Message_Relay* instance;
};

//MACROS.
#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ ":" S2(__LINE__)
#define LOG_DEBUG(message) Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, message, LOCATION));
#define LOG_INFO(message, location) Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::INFO_MESSAGE, message, location));
#define LOG_ERROR(message, location) Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, message, location));

#endif // !SYSTEM_MESSAGE_INTERFACE_H
