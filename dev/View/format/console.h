#include "format.h"

class Console_Format : public Format
{
	std::map<std::string, View*> view_tree;
	void initalize();
	void add_view(std::string handle, View* view);

	void show_all();
};
