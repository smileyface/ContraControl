#include "desktop_main.h"


std::map<std::string, Desktop_View*> CC_Window_Tree_Interface::view_tree;
std::string CC_Window_Tree_Interface::main_window_handle = "Main";

void CC_Window_Tree_Interface::initalize()
{
	view_tree.emplace(std::make_pair(main_window_handle, new Main_View("Simple Window", "Contra Control", 10)));
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
