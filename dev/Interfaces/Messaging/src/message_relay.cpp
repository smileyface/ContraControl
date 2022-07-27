#include "Messaging/message_relay.h"

#include <algorithm>
#include <mutex>
#include <string>

#include "Messaging/message_types/logging_message.h"

std::mutex g_pages_mutex;
Message_Relay* Message_Relay::instance;

Message_Relay::Message_Relay()
{ }

Consumer_List Message_Relay::get_message_consumers(Internal_Message* message)
{
	Consumer_List registered_consumers;
	for(auto i = list_of_registered_consumers.begin(); i != list_of_registered_consumers.end(); ++i)
	{
		if((*i)->correct_type(message))
		{
			registered_consumers.push_back(*i);
		}
	}
	return registered_consumers;
}

void Message_Relay::push(Internal_Message* message)
{
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	Consumer_List registered_consumers = get_message_consumers(message);
	list_of_message.emplace_back(std::make_pair(message, registered_consumers));
	for(int i = 0; i < registered_consumers.size(); i++)
	{
		registered_consumers[i]->notify();
	}
}

Internal_Message* get_found_message(Message_Consumer* consumer, std::pair<Internal_Message*, Consumer_List>& current_message)
{
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	auto it = std::find(current_message.second.begin(), current_message.second.end(), consumer);
	if(it != current_message.second.end())
	{
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
			if(it != list_of_message.end())
				list_of_message.erase(it);

			//if the consumer doesn't have another message on the relay
			if(!more_messages(consumer, list_of_message))
				consumer->freshen();
			return message;
		}
	}
	return 0;
}

int Message_Relay::number_of_messages(Message_Consumer* mc)
{
	int number_of_messages = 0;
	for(int i = 0; i < list_of_message.size(); i++)
	{
		Internal_Message* message = get_found_message(mc, list_of_message[i]);
		if(message != 0)
		{
			number_of_messages++;
		}
	}
	return number_of_messages;
}

Internal_Message* Message_Relay::front(Message_Consumer* mc)
{
	int number_of_messages = 0;
	for(int i = 0; i < list_of_message.size(); i++)
	{
		Internal_Message* message = get_found_message(mc, list_of_message[i]);
		if(message != 0)
		{
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
		if(mc->correct_type(list_of_message[i].first))
		{
			list_of_message[i].second.push_back(mc);
		}
	}
}

void Message_Relay::deregister_consumer(Message_Consumer* mc)
{
	auto consumer = std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), mc);
	list_of_registered_consumers.erase(consumer);
	for(int i = 0; i < list_of_message.size(); i++)
	{
		Internal_Message* message = get_found_message(mc, list_of_message[i]);
		if(message != 0)
		{
			auto it = std::remove_if(list_of_message.begin(), list_of_message.end(), remove_func);
			if(it != list_of_message.end())
				list_of_message.erase(it);
		}
	}
}

Message_Relay* Message_Relay::get_instance()
{
	if(instance == NULL)
	{
		instance = new Message_Relay();
	}
	return instance;
}