#include <limits>
#include <iostream>

#include "../console_format/console_option_popup.h"
#include "Messaging/message_relay.h"

void Console_Option_Popup::on_display()
{
}

void Console_Option_Popup::on_paint()
{ }

void Console_Option_Popup::on_refresh()
{ }

void Console_Option_Popup::on_input()
{
	int input;
	while(true)
	{
		std::cin >> input;

		if(std::cin.fail())
		{
			std::cerr << "Sorry, I cannot read that. Please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if(input < 1 || input > options.size() + 1)
		{
			std::cerr << "Sorry, the number is out of range." << std::endl;
			continue;
		}
		choice = input;
		break;
	}
}

bool Console_Option_Popup::is_stale()
{
	return false;
}

void Console_Option_Popup::set_options(std::vector<std::string> list_of_options)
{
	options = list_of_options;
}

int Console_Option_Popup::get_option()
{
	return choice;
}