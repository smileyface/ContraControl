#include <string>
#include <vector>

#include "../view_interface.h"
#include "../View/view_main.h"

void View_Interfaces::Main_Interface::stop_view()
{
	view::stop_view();
}

void View_Interfaces::Main_Interface::start_view()
{
	view::initalize();
	view::start_view();
}

void View_Interfaces::Main_Interface::add_view(int view_type)
{
	view::add_display(static_cast<DISPLAY_TYPES>(view_type));
}

int View_Interface_Base::create_option_popup(std::vector<std::string> option_list)
{
	return -1;
}
