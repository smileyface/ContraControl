/*****************************************************************//**
 * \file   message_relay.h
 * \brief
 *
 * \author kason
 * \date   June 2021
 *********************************************************************/
#ifndef SYSTEM_MESSAGE_INTERFACE_H
#define SYSTEM_MESSAGE_INTERFACE_H

#include <map>
#include <set>

#include "Messaging/consumers.h"
 //Messaging types

/**
 * @brief A basic structure for comparisons.
 */
struct Compare_Message
{
	/**
	 * Compare operator
	 * @param lhs Left hand variable
	 * @param rhs Right hand variable
	 * @return If left is less than the right.
	 */
	bool operator()(const Message_Ptr<Internal_Message> lhs, const Message_Ptr<Internal_Message> rhs) const
	{
		return (lhs.get()) < (rhs.get());
	}
};

/**
 * A node for the Message map based on message address and consumer list.
 */
typedef std::pair<Message_Ptr<Internal_Message> const, Consumer_List> Message_Map_Node;

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
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return first message on the relay for the requesting Consumer.
	 */
	Message_Ptr<Internal_Message> pop(Message_Consumer* consumer);

	/**
	 * Get the first message from the Message Relay for a Message Consumer.
	 *
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return An instance of the first message on the relay for the requesting Consumer.
	 */
	template<typename Message_Type>
	Message_Type pop(Message_Consumer* consumer)
	{
		return pop(consumer).convert_type<Message_Type>();
	}

	/**
	 * Get if there are messages for the consumer in the relay.
	 *
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return number of messages in the relay
	 */
	int number_of_messages(Message_Consumer* consumer);

	/**
	 * Get the number of consumers on the relay
	 * 
	 * \return number of consumers on the relay.
	 */
	int number_of_consumers();

	/**
	 * Get an instance of the first message in the front of the list. Does not remove the object from the message relay.
	 *
	 * \param consumer Pointer to the consumer requesting to get its messages.
	 * \return Pointer to the first message
	 */
	Message_Ptr<Internal_Message> front(Message_Consumer* consumer);

	/**
	 * Get instance of the singleton.
	 * \return Instance of the message relay.
	 */
	static Message_Relay* get_instance();

	/**
	Destroy the instance of the singleton
	*/
	static void destroy_instance();

	/**
	 * Register consumer for message consumption.
	 * \param consumer Add a Message_Consumer to the list of known consumers. You must do this before you are able to recieve messages.
	 * \return A pointer to the consumer on the relay
	 */
	template<typename Message_Type>
	Message_Consumer* register_consumer()
	{
		Message_Consumer* new_consumer = new Message_Consumer(new Message_Type());
		auto return_status = list_of_registered_consumers.insert(new_consumer);
		if(return_status.second)
		{
			for(auto current_message = list_of_message.begin(); current_message != list_of_message.end(); current_message++)
			{
				if(new_consumer->correct_type(current_message->first.get()))
				{
					current_message->second.push_back(new_consumer);
				}
			}
		}
		return new_consumer;
	}

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


private:
	Message_Relay();
	std::map<Message_Ptr<Internal_Message>, Consumer_List, Compare_Message> list_of_message;
	std::set<Message_Consumer*> list_of_registered_consumers;
	static Message_Relay* instance;

	Consumer_List get_message_consumers(Internal_Message* message);
	void freshen_messages(Message_Consumer* consumer);
	bool more_messages(Message_Consumer* consumer);
	void remove_unwanted_messages();
	void remove_consumer_from_messages(Message_Consumer* consumer, Consumer_List& messages);
	Message_Ptr<Internal_Message> get_found_message(Message_Consumer* consumer, Message_Map_Node& current_message);
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
