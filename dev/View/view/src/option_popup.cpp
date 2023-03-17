#include <limits>
#include <iostream>

#include "../console_format/console_option_popup.h"
#include "../view_type/option_view_type.h"
#include "Messaging/message_relay.h"

Option_View_Type::Option_View_Type()
{
	specified_message;
	option_consumer = Message_Relay::get_instance()->register_consumer<Option_Popup_Message>();
}

void Option_View_Type::get_message()
{
	specified_message = Message_Relay::get_instance()->pop<Option_Popup_Message>(option_consumer);
	message.OPTIONS = specified_message.get_options();
	message.QUERY = specified_message.get_option_query();
}

Console_Option_Popup::~Console_Option_Popup()
{ 
}

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
		painted_message += std::to_string(i+1) + ")";
		for(int j = std::to_string(i+1).size(); j < 4; j++)
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
	if(!displayed || keyboard.get_timed_out())
	{
		return;
	}
	//TODO Make the input be a response message.
	option_input = keyboard.get_number();
	if(option_input < 1 || option_input > options.size() + 1)
	{
		if(keyboard.get_timed_out())
		{
			LOG_ERROR("Selection timed out", "Option Popup Query");
		}
		else
		{
			LOG_ERROR("Selection outside of range of choices", "Option Popup Query");
		}
	}
	else
	{
		LOG_DEBUG("Valid option selected: " + option_input);
		exit();
	}


	choice = option_input;
}

void Console_Option_Popup::on_input()
{
	if(choice > -1 || !keyboard.get_timed_out())
	{
		Message_Relay::get_instance()->push(new Option_Popup_Response_Message(choice, specified_message));
	}
}

void Console_Option_Popup::on_destroy()
{
	Message_Relay::get_instance()->deregister_consumer(option_consumer);
}

bool Console_Option_Popup::is_stale()
{
	return stale;
}

bool Console_Option_Popup::quit()
{
	return choice > 0 || keyboard.get_timed_out() || Console_View::quit();
}

void Console_Option_Popup::set_options(std::string query,std::vector<std::string> list_of_options)
{
	options = list_of_options;
}

int Console_Option_Popup::get_option()
{
	return choice;
}