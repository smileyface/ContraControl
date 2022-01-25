#include "Interfaces/main_interface.h"

#include "Interfaces/controller_interface.h"
#include "Interfaces/model_interface.h"
#include "Interfaces/view_interface.h"
void Main_Interfaces::Controller_Interface::start_controller()
{
	Controller_Interfaces::Main_Interface::start_controller();
}

void Main_Interfaces::Model_Interface::start_model()
{
	Model_Interfaces::Main_Interface::start_model();
}

void Main_Interfaces::View_Interface::start_view()
{
	View_Interfaces::Main_Interface::start_view();
}

void Main_Interfaces::Controller_Interface::stop_controller()
{
	Controller_Interfaces::Main_Interface::stop_controller();
}

void Main_Interfaces::Model_Interface::stop_model()
{
	Model_Interfaces::Main_Interface::stop_model();
}

void Main_Interfaces::View_Interface::stop_view()
{
	View_Interfaces::Main_Interface::stop_view();
}

void Main_Interfaces::View_Interface::add_view(int view)
{
	View_Interfaces::Main_Interface::add_view(view);
}
