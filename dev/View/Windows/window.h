#ifndef WINDOW_TREE
#define WINDOW_TREE


#include <map>
#include <string>
#include "views.h"

namespace CC_Window_Tree_Interface
{
	extern std::string main_window_handle;
	extern std::map<std::string, View*> window_tree;
	void initalize(HINSTANCE hInstance);
	void show_all();
	View* getWindow(HWND hwnd);


}

#endif // !WINDOW_TREE