#ifndef VIEW_FORMAT_INCLUDE_H
#define VIEW_FORMAT_INCLUDE_H

#include <string>

#include "Interfaces/enums/view_type_enum.h"
#include "Interfaces/enums/display_type_enum.h"

#include "../view/view.h"

class Format
{
public:

	virtual void initalize() = 0;
	virtual DISPLAY_TYPES get_display_type() = 0;
	virtual void add_view(VIEW_TYPE_ENUM view);
	void update_views();
	void clean_views();

	void start_display();
	void stop_display();
	virtual void loop() = 0;

	std::vector<View*> view_list;
private:
	bool format_running = false;
};

#endif