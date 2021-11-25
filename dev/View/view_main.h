#ifndef VIEW_EXECUTOR_H
#define VIEW_EXECUTOR_H
#include <vector>

#include "format/format.h"
#include "../Interfaces/Interfaces/enums/display_type_enum.h"

namespace view
{
	extern std::vector<Format*> list_of_formats;
	extern bool view_running;

	void initalize();
	void start_view();
	int add_display(DISPLAY_TYPES display);
}


#endif