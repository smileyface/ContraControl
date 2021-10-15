#include "view_main.h"

#include "format/console.h"
#include "view/views.h"

std::vector<Format*> view::list_of_formats = {};
bool view::view_running = false;

void view::initalize()
{

}

void view::start_view()
{

	list_of_formats[0]->add_view("System", new Console_System_View());
	//THIS IS DEBUG LINE

	//END DEBUG LINE
}

void view::add_display(DISPLAY_TYPES display)
{
	switch (display)
	{
	case DISPLAY_TYPES::CONSOLE:
		list_of_formats.emplace_back(new Console_Format());
		break;
	}
}
