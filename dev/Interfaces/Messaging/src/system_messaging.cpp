#include "Messaging/system_messaging.h"

#include <algorithm>
#include <mutex>
#include <string>

std::mutex g_pages_mutex;

std::string message_priority_as_string(MESSAGE_PRIORITY al)
{
	std::string level;
	switch (al)
	{
	case MESSAGE_PRIORITY::SEVERE_MESSAGE:
		return "SEVERE";
	case MESSAGE_PRIORITY::INFO_MESSAGE:
		return "INFO";
	case MESSAGE_PRIORITY::ERROR_MESSAGE:
		return "ERROR";
	case MESSAGE_PRIORITY::DEBUG_MESSAGE:
		return "DEBUG";
	default:
		return "UNHANDLED PRIORITY";
	}
	return level;
}

System_Message::System_Message(MESSAGE_PRIORITY pri, std::string msg, std::string loc)
{
	priority = pri;
	message = msg;
	location = loc;
	valid_message = true;
}

System_Message::System_Message(bool vm)
{
	priority = MESSAGE_PRIORITY::INFO_MESSAGE;
	message = "";
	location = "";
	valid_message = vm;
}

System_Messages* System_Messages::instance;

System_Messages::System_Messages()
{
}

void System_Messages::push(System_Message message)
{
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_message.emplace_back(std::make_pair(message, list_of_registered_consumers));
	for (int i = 0; i < list_of_registered_consumers.size(); i++)
	{
		list_of_registered_consumers[i]->notify();
	}
	
}

System_Message get_found_message(Message_Consumer* consumer, std::pair<System_Message, Consumer_List>& current_message)
{
	auto it = std::find(current_message.second.begin(), current_message.second.end(), consumer);
	System_Message found_message(false);
	if (it != current_message.second.end())
	{
		std::lock_guard<std::mutex> guard(g_pages_mutex);
		found_message = current_message.first;
		current_message.second.erase(it);
	}
	return found_message;
}

bool remove_func(std::pair<System_Message, Consumer_List> Message_Data)
{
	return Message_Data.second.size() == 0;
}

bool more_messages(Message_Consumer* consumer, std::vector<std::pair<System_Message, Consumer_List>> messages)
{
	for (int i = 0; i < messages.size(); i++)
	{
		auto it = std::find(messages[i].second.begin(), messages[i].second.end(), consumer);
		if (it != messages[i].second.end())
		{
			return true;
		}
	} 
	return false;
}

System_Message System_Messages::pop(Message_Consumer* consumer)
{
	System_Message message(false);
	for (int i = 0; i < list_of_message.size(); i++)
	{
		message = get_found_message(consumer, list_of_message[i]);
		if (message.valid_message == true)
		{
			break;
		}
	}
	
	auto it = std::remove_if(list_of_message.begin(), list_of_message.end(), remove_func);
	list_of_message.erase(it, list_of_message.end());

	//if we don't have another message on the relay
	if(!more_messages(consumer, list_of_message))
		consumer->freshen();
	return message;
}

void System_Messages::register_consumer(Message_Consumer* mc)
{
	list_of_registered_consumers.push_back(mc);
	for (int i = 0; i < list_of_message.size(); i++)
	{
		list_of_message[i].second.push_back(mc);
	}
}

void System_Messages::deregister_consumer(Message_Consumer* mc)
{
	auto consumer = std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), mc);
	list_of_registered_consumers.erase(consumer);
}

System_Messages* System_Messages::get_instance()
{
	if (instance == nullptr)
	{
		instance = new System_Messages();
	}
	return instance;
}
