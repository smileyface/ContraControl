#include "view_main.h"

#include "format/console.h"
#include "view/views.h"

std::vector<Format*> view::list_of_formats = {};
bool view::view_running = false;
int display_id = 0;

void view::initalize()
{

}

void view::start_view()
{

	list_of_formats[0]->add_view(VIEW_TYPE_ENUM::SYSTEM);
	//THIS IS DEBUG LINE

	//END DEBUG LINE
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
