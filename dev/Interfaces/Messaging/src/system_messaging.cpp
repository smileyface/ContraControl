#include "Messaging/system_messaging.h"

#include <algorithm>
#include <mutex>
#include <string>

#include "Messaging/message_types/logging_message.h"

std::mutex g_pages_mutex;
Message_Relay* Message_Relay::instance;

Message_Relay::Message_Relay()
{ }

void Message_Relay::push(Internal_Message* message)
{
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_message.emplace_back(std::make_pair(message, list_of_registered_consumers));
	for(int i = 0; i < list_of_registered_consumers.size(); i++)
	{
		list_of_registered_consumers[i]->notify();
	}
}

Internal_Message* get_found_message(Message_Consumer* consumer, std::pair<Internal_Message*, Consumer_List>& current_message)
{
	auto it = std::find(current_message.second.begin(), current_message.second.end(), consumer);
	if(it != current_message.second.end())
	{
		std::lock_guard<std::mutex> guard(g_pages_mutex);
		Internal_Message* found_message = current_message.first;
		current_message.second.erase(it);
		return found_message;
	}
	return 0;
}

bool remove_func(std::pair<Internal_Message*, Consumer_List> Message_Data)
{
	return Message_Data.second.size() == 0;
}

bool more_messages(Message_Consumer* consumer, std::vector<std::pair<Internal_Message*, Consumer_List>> messages)
{
	for(int i = 0; i < messages.size(); i++)
	{
		auto it = std::find(messages[i].second.begin(), messages[i].second.end(), consumer);
		if(it != messages[i].second.end())
		{
			return true;
		}
	}
	return false;
}

Internal_Message* Message_Relay::pop(Message_Consumer* consumer)
{
	for(int i = 0; i < list_of_message.size(); i++)
	{
		Internal_Message* message = get_found_message(consumer, list_of_message[i]);
		if(message != 0)
		{
			auto it = std::remove_if(list_of_message.begin(), list_of_message.end(), remove_func);
			list_of_message.erase(it, list_of_message.end());

			//if the consumer doesn't have another message on the relay
			if(!more_messages(consumer, list_of_message))
				consumer->freshen();
			return message;
		}
	}
	return 0;
}

void Message_Relay::register_consumer(Message_Consumer* mc)
{
	list_of_registered_consumers.push_back(mc);
	for(int i = 0; i < list_of_message.size(); i++)
	{
		list_of_message[i].second.push_back(mc);
	}
}

void Message_Relay::deregister_consumer(Message_Consumer* mc)
{
	auto consumer = std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), mc);
	list_of_registered_consumers.erase(consumer);
}

Message_Relay* Message_Relay::get_instance()
{
	if(instance == nullptr)
	{
		instance = new Message_Relay();
	}
	return instance;
}