#include "..\format.h"

void Format::add_view(std::string handle, View* view)
{
	view_tree.insert(view);
}

void Format::update_views()
{
	for (auto i = view_tree.begin(); i != view_tree.end(); i++)
	{
		if (i->second->is_stale())
		{
			i->second->on_refresh();
			i->second->on_paint();
			i->second->on_display();
		}
	}
}

void Format::clean_views()
{
	for (auto i = view_tree.begin(); i != view_tree.end(); i++)
	{
		i->second->on_destroy();
	}
}
