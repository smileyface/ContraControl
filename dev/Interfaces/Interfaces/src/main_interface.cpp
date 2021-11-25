#include "Interfaces/main_interface.h"

#include "Interfaces/controller_interface.h"
#include "../View/view_main.h"
void Main_Interfaces::Controller_Interface::start_controller()
{
	Controller_Interfaces::Main_Interface::start_controller();
}

void Main_Interfaces::View_Interface::start_view()
{
	view::start_view();
}


int Main_Interfaces::View_Interface::add_display(DISPLAY_TYPES display)
{
	 return view::add_display(display);
}

void Main_Interfaces::View_Interface::add_view(VIEW_TYPE_ENUM view)
{
	
}

void Main_Interfaces::View_Interface::initalize(std::vector<DISPLAY_TYPES> types)
{
	for (std::vector<DISPLAY_TYPES>::iterator type = types.begin(); type != types.end(); type++)
	{
		view::add_display(*type);
	}
	view::initalize();
}
