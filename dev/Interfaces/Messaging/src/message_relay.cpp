#include "Messaging/message_relay.h"

#include <algorithm>
#include <mutex>
#include <string>
#include <iostream>

std::mutex g_pages_mutex;
Message_Relay* Message_Relay::instance;

Internal_Message* Message_Relay::get_found_message(Message_Consumer* consumer, Message_Map_Node& current_message)
{
	Internal_Message* found_message = 0;
	if(current_message.second.size() > 0)
	{
		auto it = current_message.second.begin();
		while(it != current_message.second.end())
		{
			if(*it == consumer)
			{
				break;
			}
			it++;
		}
		if(it != current_message.second.end())
				found_message = current_message.first;
	}
	return found_message;
}

void Message_Relay::remove_consumer_from_messages(Message_Consumer* consumer, Consumer_List& messages)
{
	auto it = std::find(messages.begin(), messages.end(), consumer);
	if(it != messages.end())
	{
		g_pages_mutex.lock();
		messages.erase(it);
		g_pages_mutex.unlock();
	}
}

bool Message_Relay::more_messages(Message_Consumer* consumer)
{
	bool messages_found = number_of_messages(consumer) > 0;
	return messages_found;
}

void Message_Relay::remove_unwanted_messages()
{
	auto it = list_of_message.begin();
	while( it != list_of_message.end() )
	{
		if(it->second.size() == 0)
		{
			const std::lock_guard<std::mutex> lock(g_pages_mutex);
			it = list_of_message.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Message_Relay::freshen_messages(Message_Consumer* consumer)
{
	//if the consumer doesn't have another message on the relay
	if(!more_messages(consumer))
		consumer->freshen();
}

Message_Relay::Message_Relay()
{ }

Message_Relay::~Message_Relay()
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
	Consumer_List registered_consumers = get_message_consumers(message);
	g_pages_mutex.lock();
	list_of_message[message] = registered_consumers;
	g_pages_mutex.unlock();
	for(int i = 0; i < registered_consumers.size(); i++)
	{
		registered_consumers[i]->notify();
	}
}

Internal_Message* Message_Relay::pop(Message_Consumer* consumer)
{
	Internal_Message* message = 0;
	for(auto current_message = list_of_message.begin(); current_message != list_of_message.end(); current_message++)
	{
		message = front(consumer);
		if(message != 0)
		{
			remove_consumer_from_messages(consumer, list_of_message[message]);
			freshen_messages(consumer);
			break;
		}
	}
	remove_unwanted_messages();
	return message;
}

int Message_Relay::number_of_messages(Message_Consumer* mc)
{
	int number_of_messages = 0;
	for(auto current_message = list_of_message.begin(); current_message != list_of_message.end(); current_message++)
	{
		Internal_Message* message = get_found_message(mc, *current_message);
		if(message != 0)
		{
			number_of_messages++;
		}
	}
	return number_of_messages;
}

Internal_Message* Message_Relay::front(Message_Consumer* mc)
{
	Internal_Message* message = 0;
	for(auto i = list_of_message.begin(); i != list_of_message.end(); i++)
	{
		if(get_found_message(mc, (*i)) != 0)
		{
			message = i->first;
			break;
	
		}
	}
	return message;
}

Message_Consumer* Message_Relay::register_consumer(const Internal_Message* mess)
{
	Message_Consumer* new_consumer = new Message_Consumer(mess);
	auto return_status = list_of_registered_consumers.insert(new_consumer);
	if(return_status.second)
	{
		for(auto current_message = list_of_message.begin(); current_message != list_of_message.end(); current_message++)
		{
			if(new_consumer->correct_type(current_message->first))
			{
				current_message->second.push_back(new_consumer);
			}
		}
	}
	return new_consumer;
}

void Message_Relay::deregister_consumer(Message_Consumer* mc)
{
	auto consumer = std::find(list_of_registered_consumers.begin(), list_of_registered_consumers.end(), mc);
	if(consumer != std::end(list_of_registered_consumers))
	{
		for(auto current_message = list_of_message.begin(); current_message != list_of_message.end(); current_message++)
		{
			Internal_Message* message = get_found_message(mc, (*current_message));
			if(message != 0)
			{
				remove_consumer_from_messages(mc, list_of_message[message]);
			}
		}
		delete* consumer;
		list_of_registered_consumers.erase(consumer);
		remove_unwanted_messages();
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

void Message_Relay::destroy()
{
	delete instance;
	instance = NULL;
}

void Message_Relay::clear()
{ 
	std::lock_guard<std::mutex> guard(g_pages_mutex);
	list_of_message.clear();
	list_of_registered_consumers.clear();
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
