#include "../console_option_popup.h"

#include <iostream>

#include "Messaging/message_relay.h"

void Console_Option_Popup::on_display()
{
	std::cout << painted_message << std::endl;
	displayed = true;
}

void Console_Option_Popup::on_paint()
{
	painted_message = options_query + "\n";
	for(int i = 0; i < options.size(); i++)
	{
		painted_message += std::to_string(i + 1) + ")";
		for(int j = std::to_string(i + 1).size(); j < 4; j++)
		{
			painted_message += " ";
		}
		painted_message += options[i] + "\n";
	}
}

void Console_Option_Popup::on_refresh()
{
	get_message();
	options = message.OPTIONS;
	options_query = message.QUERY;
}

void Console_Option_Popup::on_query()
{
	int option_input;
	if(!displayed)
	{
		return;
	}
	while(true)
	{
		//TODO Make the input be a response message.
		//input = keyboard->get_number(); 
		option_input = 1;
		if(option_input > options.size())
		{
			LOG_ERROR("Selection outside of range of choices", "Option Popup");
		}

		if(option_input < 1 || option_input > options.size() + 1)
		{
			std::cerr << "Sorry, the number is out of range." << std::endl;
			continue;
		}
		choice = option_input;
		break;
	}
}

void Console_Option_Popup::on_create()
{
	Option_View_Type::create();
	Console_View::on_create();
}

void Console_Option_Popup::on_destroy()
{
	Option_View_Type::destroy();
	Console_View::on_destroy();
}

void Console_Option_Popup::on_input()
{
	if(choice < 0)
	{
		return;
	}
	Option_Popup_Response_Message* response = new Option_Popup_Response_Message(choice, &specified_message);
	Message_Relay::get_instance()->push(response);
}

bool Console_Option_Popup::is_stale()
{
	return !displayed || option_consumer->is_stale();
}

bool Console_Option_Popup::quit()
{
	return choice > 0 || quiter;
}

void Console_Option_Popup::set_options(std::string query, std::vector<std::string> list_of_options)
{
	options = list_of_options;
}

const int Console_Option_Popup::get_option()
{
	return choice;
}