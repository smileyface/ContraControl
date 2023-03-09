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

void view::remove_all()
{ 
	for(auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator)->remove();
		delete* (iterator);
	}

	list_of_formats.erase(list_of_formats.begin(), list_of_formats.end());
}

void view::start_view()
{
	view::initalize();
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
	view_running = false;
	view::remove_all();
}


int view::add_display(DISPLAY_TYPES display)
{
	int my_display_id = display_id;
	display_id++;
	Format* format_ptr = 0;
	switch (display)
	{
	case DISPLAY_TYPES::CONSOLE:
		format_ptr = new Console_Format();
		break;
	}
	if(view_running)
	{
		format_ptr->initalize();
		format_ptr->start_display();
	}                                 
	list_of_formats.push_back(format_ptr);
	return my_display_id;
}