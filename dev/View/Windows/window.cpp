#include "window.h"


std::map<std::string, View*> CC_Window_Tree_Interface::window_tree;
std::string CC_Window_Tree_Interface::main_window_handle = "Main";

void CC_Window_Tree_Interface::initalize(HINSTANCE hInstance)
{
	window_hInstance = hInstance;
	window_tree.emplace(std::make_pair(main_window_handle, new Main_View("Simple Window", "Contra Control", 10)));
}

void CC_Window_Tree_Interface::show_all()
{
	std::map<std::string, View*>::iterator it;
	for (it = window_tree.begin(); it != window_tree.end(); it++)
	{
		window_tree[it->first]->display();
	}
}

View* CC_Window_Tree_Interface::getWindow(HWND hwnd)
{
	std::map<std::string, View*>::iterator it;
	for (it = window_tree.begin(); it != window_tree.end(); it++)
	{
		if (*window_tree[it->first] == hwnd)
		{
			return window_tree[it->first];
		}
	}
	throw "This window does not exist";
}
