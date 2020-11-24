#include "desktop_main.h"


std::map<std::string, Desktop_View*> CC_Window_Tree_Interface::view_tree;
std::string CC_Window_Tree_Interface::main_window_handle = "Main";

void CC_Window_Tree_Interface::initalize()
{
	add_view(main_window_handle, new Main_View());
}

void CC_Window_Tree_Interface::add_view(std::string handle, Desktop_View* view)
{
	view_tree.emplace(std::make_pair(handle, view));
	view_tree[handle]->initalize(handle, handle);
}

void CC_Window_Tree_Interface::show_all()
{
	std::map<std::string, Desktop_View*>::iterator it;
	for (it = view_tree.begin(); it != view_tree.end(); it++)
	{
		view_tree[it->first]->display();
	}
}

View* CC_Window_Tree_Interface::getWindow(View* hwnd)
{
	std::map<std::string, Desktop_View*>::iterator it;
	for (it = view_tree.begin(); it != view_tree.end(); it++)
	{
		if (view_tree[it->first] == hwnd)
		{
			return view_tree[it->first];
		}
	}
	throw "This window does not exist";
}
