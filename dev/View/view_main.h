#ifndef VIEW_MAIN_H
#define VIEW_MAIN_H
#include <vector>

#include "format/format.h"

namespace view
{
	void initalize();
	void start_view();
	void add_display(int display);

	std::vector<Format> list_of_formats;
	bool view_running = false;

	enum
	{
		Console_Display = 0
	};
}

#endif