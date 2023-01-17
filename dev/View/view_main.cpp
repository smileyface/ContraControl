#include "view_main.h"

#include "format/console.h"
#include "view/views.h"

std::vector<Format*> view::list_of_formats = {};
bool view::view_running = false;
int display_id = 0;

void view::initalize()
{
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator)->initalize();
	}
}

void view::start_view()
{
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator)->start_display();
	}
	view_running = true;
}

void view::stop_view()
{
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator)->stop_display();
	}
	for(auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		while((*iterator)->running())
		{

		}
	}
	view_running = false;
}

int view::add_display(DISPLAY_TYPES display)
{
	int my_display_id = display_id;
	display_id++;
	switch (display)
	{
	case DISPLAY_TYPES::CONSOLE:
		list_of_formats.emplace_back(new Console_Format());
		break;
	}
	return my_display_id;
}
