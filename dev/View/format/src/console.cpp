#include <iostream>
#include <thread>

#include "../console.h"
#include "../../view/view.h"
#include "../../factories/view_factory.h"

void Console_Format::initalize()
{
	std::cout << "I LIVE" << std::endl;
	add_view(VIEW_TYPE_ENUM::SYSTEM);
}

void Console_Format::add_view(VIEW_TYPE_ENUM view)
{
	std::cout << "Adding View: " << get_view_type_enum_as_string(view) << std::endl;
	view_list.push_back(view_factory(view, DISPLAY_TYPES::CONSOLE));
}

void Console_Format::start_format()
{
	format_running = true;
}

bool Console_Format::is_running()
{
	return format_running;
}

void Console_Format::loop()
{
	while (format_running)
	{
		update_views();
	}
}
