#include "../commander.h"

Commander* Commander::instance = nullptr;

Commander* Commander::get_instance()
{
	if(instance == nullptr)
	{
		instance = new Commander();
	}
	return instance;
}

void Commander::clean_list()
{ 
	for(auto i = command_list.begin(); i != command_list.end();)
	{
		if((*i)->completed())
		{
			delete* i;
			i = command_list.erase(i);
		}
		else
		{
			i++;
		}
	}
}
