#include "Messaging/message_relay.h"

#include <algorithm>
#include <mutex>
#include <string>
#include <iostream>

std::mutex g_pages_mutex;
Message_Relay* Message_Relay::instance;

Internal_Message* get_found_message(Message_Consumer* consumer, std::pair<Internal_Message*, Consumer_List>& current_message)
{
	Internal_Message* found_message = 0;
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	if(current_message.second.size() > 0)
	{
		auto it = std::find(current_message.second.begin(), current_message.second.end(), consumer);
		if(it != current_message.second.end())
				found_message = current_message.first;
	}
	return found_message;
}

void  remove_consumer_from_messages(Message_Consumer* consumer, std::pair<Internal_Message*, Consumer_List>& messages)
{
	auto it = std::find(messages.second.begin(), messages.second.end(), consumer);
	if(it != messages.second.end())
	{
		std::lock_guard<std::mutex> guard(g_pages_mutex);
		messages.second.erase(it);
	}
}

bool remove_func(std::pair<Internal_Message*, Consumer_List> Message_Data)
{
	return Message_Data.second.size() == 0;
}

bool more_messages(Message_Consumer* consumer, std::vector<std::pair<Internal_Message*, Consumer_List>> messages)
{
	for(int i = 0; i < messages.size(); i++)
	{
		if(std::find(messages[i].second.begin(), messages[i].second.end(), consumer) != messages[i].second.end())
		{
			return true;
		}
	}
	return false;
}

void remove_unwanted_messages(std::vector<std::pair<Internal_Message*, Consumer_List>>& list_of_message)
{
	auto it = std::remove_if(list_of_message.begin(), list_of_message.end(), remove_func);
	if(it != list_of_message.end())
	{
		const std::lock_guard<std::mutex> lock(g_pages_mutex);
		list_of_message.erase(it);
	}
}

void freshen_messages(Message_Consumer* consumer, std::vector<std::pair<Internal_Message*, Consumer_List>>& list_of_message)
{
	//if the consumer doesn't have another message on the relay
	if(!more_messages(consumer, list_of_message))
		consumer->freshen();
}

Message_Relay::Message_Relay()
{ }

Message_Relay::~Message_Relay()
{
	delete instance;
}

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

Internal_Message* Message_Relay::pop(Message_Consumer* consumer)
{
	Internal_Message* message = 0;
	for(int i = 0; i < list_of_message.size(); i++)
	{
		message = get_found_message(consumer, list_of_message[i]);
		if(message != 0)
		{
			remove_consumer_from_messages(consumer, list_of_message[i]);
			freshen_messages(consumer, list_of_message);
			break;
		}
	}
	remove_unwanted_messages(list_of_message);
	return message;
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
	Internal_Message* message = 0;
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
	if(std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), mc) == list_of_registered_consumers.end())
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
}

void Message_Relay::deregister_consumer(Message_Consumer* mc)
{
	auto consumer = std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), mc);
	if(consumer != std::end(list_of_registered_consumers))
	{
		list_of_registered_consumers.erase(consumer);
		for(int i = 0; i < list_of_message.size(); i++)
		{
			Internal_Message* message = get_found_message(mc, list_of_message[i]);
			if(message != 0)
			{
				remove_consumer_from_messages(mc, list_of_message[i]);
			}
		}
		remove_unwanted_messages(list_of_message);
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

void Message_Relay::clear()
{ 
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_message.clear();
}

bool Message_Relay::has_consumer(Message_Consumer* consumer)
{
	auto found = std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), consumer);
	return found != list_of_registered_consumers.end();
}

int Message_Relay::number_of_consumers()
{
	return list_of_registered_consumers.size();
}

const Logging_Message* Message_Types::LOGGING = new Logging_Message();
const View_Subsystem_Message* Message_Types::VIEW_SUBSYSTEM = new View_Subsystem_Message();
const Option_Popup_Message* Message_Types::OPTION_POPUP_REQUEST = new Option_Popup_Message();
const Response_Message* Message_Types::RESPONSE = new Response_Message();
const Option_Popup_Response_Message* Message_Types::OPTION_POPUP_RESPONSE = new Option_Popup_Response_Message();
