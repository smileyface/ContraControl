#include "../../view/console_format/console_view.h"


Device_View::Device_View() :
	quiter(false)
{ 
}

Device_View::~Device_View()
{ 
}

void Device_View::quit_view()
{ 
	quiter = true;
}
