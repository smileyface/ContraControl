#include "../../view/console_format/console_view.h"


View::View() :
	quiter(false)
{ 
}

View::~View()
{ 
}

void View::quit_view()
{ 
	quiter = true;
}
