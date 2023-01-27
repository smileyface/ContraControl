/*****************************************************************//**
 * \file   message_relay.h
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
#include "internal_messages.h"

/**
 * Message relay system as a singleton.
 *
 * \todo rename to Message_Relay
 */
class Message_Relay
{
public:
	~Message_Relay();
	/**
	 * Push a message to the Message Relay.
	 *
	 * \param message Message to add to the relay
	 */
	void push(Internal_Message* message);
	/**
	 * Get the first message from the Message Relay for a Message Consumer.
	 *
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return first message on the relay for the requesting Consumer.
	 */
	Internal_Message* pop(Message_Consumer* consumer);

	/**
	 * Get if there are messages for the consumer in the relay.
	 *
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return number of messages in the relay
	 */
	int number_of_messages(Message_Consumer* consumer);

	/**
	 * Get an instance of the first message in the front of the list. Does not remove the object from the message relay.
	 *
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return instance of the first message
	 */
	Internal_Message* front(Message_Consumer* consumer);

	/**
	 * Get instance of the singleton.
	 * \return Instance of the message relay.
	 */
	static Message_Relay* get_instance();
	/**
	 * Register consumer for message consumption.
	 * \param consumer Add a Message_Consumer to the list of known consumers. You must do this before you are able to recieve messages.
	 */
	void register_consumer(Message_Consumer* consumer);

	/**
	 * Remove consumer from the consumer list. The system that owns this consumer will not be able to recieve messages while deregistered.
	 * Any messages sent while not registered will just be missed.
	 * \param consumer Consumer to be removed from the list.
	 */
	void deregister_consumer(Message_Consumer* consumer);

	/**
	* Remove all messages from the relay
	*/
	void clear();

	/**
	 * \return If consumer is on the relay.
	 * \param consumer Consumer to check against.
	 */
	bool has_consumer(Message_Consumer* consumer);


private:
	Message_Relay();
	std::vector<std::pair<Internal_Message*, Consumer_List>> list_of_message;
	std::vector<Message_Consumer*> list_of_registered_consumers;
	static Message_Relay* instance;

	Consumer_List get_message_consumers(Internal_Message* message);
};

//MACROS.
/**
 * String supporting macro
 */
#define S1(x) #x
 /**
  * String supporting macro
  */
#define S2(x) S1(x)
  /**
   * Macro to get the file trace of a line
   */
#define LOCATION __FILE__ ":" S2(__LINE__)
   /**
	* Add a debugging log message.
	*/
#define LOG_DEBUG(message) Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::DEBUG_MESSAGE, message, LOCATION));
	/**
	 * Add an informational log message.
	 */
#define LOG_INFO(message, location) Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::INFO_MESSAGE, message, location));
	 /**
	  * Add an error state log message.
	  */
#define LOG_ERROR(message, location) Message_Relay::get_instance()->push(new Logging_Message(MESSAGE_PRIORITY::ERROR_MESSAGE, message, location));

#endif // !SYSTEM_MESSAGE_INTERFACE_H
