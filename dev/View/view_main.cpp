#include "view_main.h"

#include "format/console.h"

#include "view/views.h"

void view::initalize()
{
	list_of_formats.emplace_back(Console_Format());
}

void view::start_view()
{
	list_of_formats[0].add_view("System", new Console_System_View());
	//THIS IS DEBUG LINE

	//END DEBUG LINE
}

void view::add_display(int display)
{
	switch (display)
	{
	case Console_Display:
		list_of_formats.emplace_back(Console_Format());
	}
}
