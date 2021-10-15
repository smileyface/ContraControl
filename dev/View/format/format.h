#ifndef VIEW_FORMAT_INCLUDE_H
#define VIEW_FORMAT_INCLUDE_H

#include <map>
#include <string>

#include "../view/view.h"

class Format
{
public:
	std::map<std::string, View*> view_tree;

	virtual void initalize() = 0;
	void add_view(std::string handle, View* view);
	void update_views();
	void clean_views();
private:
	bool format_running = false;
};

#endif