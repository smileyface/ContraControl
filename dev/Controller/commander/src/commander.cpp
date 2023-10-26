#include "../commander.h"
#include "Messaging/message_relay.h"

Commander* Commander::instance = nullptr;

Commander::~Commander()
{
	while(!command_list.empty())
	{
		delete command_list.front();
		command_list.erase(command_list.begin());
	}
}

Commander* Commander::get_instance()
{
	if(instance == nullptr)
	{
		instance = new Commander();
	}
	return instance;
}

void Commander::destroy_instance()
{ 
	if(instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Commander::clean_list()
{ 
	for(auto i = command_list.begin(); i != command_list.end();)
	{
		if((*i)->completed())
		{
			LOG_DEBUG("Command " + ((*i)->get_id_str()) + " completed\n");
			delete* i;
			(*i) = nullptr;
			i = command_list.erase(i);
		}
		else
		{
			i++;
		}
	}
}

int Commander::get_number_of_commands()
{
	return command_list.size();
}
