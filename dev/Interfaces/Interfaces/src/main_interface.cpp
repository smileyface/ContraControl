#include "Interfaces/main_interface.h"

#include "Interfaces/controller_interface.h"
#include "../View/view_main.h"
void Main_Interfaces::Controller_Interface::start_controller()
{
	Controller_Interfaces::Main_Interface::start_controller();
}

void Main_Interfaces::View_Interface::start_view()
{
	view::initalize();
}


int Main_Interfaces::View_Interface::add_display(DISPLAY_TYPES display)
{
	view::add_display(display);
}

void Main_Interfaces::View_Interface::add_view(VIEW_TYPE_ENUM view)
{

}
