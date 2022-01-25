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
	DEBUG,
	/**
	Informational message. For verbose logging.
	*/
	INFO,
	/**
	A non-program stopping error.
	*/
	ERROR,
	/**
	A program breaking error.
	*/
	SEVERE

};

std::string message_priority_as_string(MESSAGE_PRIORITY al);


struct System_Message
{
	MESSAGE_PRIORITY priority;
	std::string message;
	std::string location;
	bool valid_message;
	System_Message(MESSAGE_PRIORITY pri, std::string msg, std::string loc);
	System_Message(bool valid_message);
};

class System_Messages
{
public:
	void push(System_Message);
	std::vector<System_Message> pop(Message_Consumer*);
	static System_Messages* get_instance();
	int get_size_of_queue();
	void register_consumer(Message_Consumer*);
private:
	System_Messages();
	std::vector<std::pair<System_Message, Consumer_List>> list_of_message;
	std::vector<Message_Consumer*> list_of_registered_consumers;
	static System_Messages* instance;

};

#endif // !SYSTEM_MESSAGE_INTERFACE_H


