#include "Interfaces/main_interface.h"

#include "../Controller/controller_main.h"
#include "../View/view_main.h"
void Main_Interfaces::Controller_Interface::start_controller()
{
	controller::initalize();
	controller::controller_running = true;
}

void Main_Interfaces::View_Interface::start_view()
{
	view::initalize();
}
