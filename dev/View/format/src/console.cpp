#include <iostream>
#include <thread>

#include "../console.h"


void Console_Format::initalize()
{
	std::cout << "I LIVE" << std::endl;
}

void Console_Format::add_view(std::string handle, View* view)
{
	std::cout << "Adding view" << std::endl;
	view_tree[handle] = view;
}

void Console_Format::console_display_thread()
{
	while (format_running)
	{
		update_views();
	}
}

void Console_Format::start_format()
{
	format_running = true;
}

bool Console_Format::is_running()
{
	return format_running;
}
