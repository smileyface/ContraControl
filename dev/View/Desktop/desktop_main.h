#ifndef WINDOW_TREE
#define WINDOW_TREE


#include <map>
#include <string>
#include "views.h"
#include "Interfaces/interfaces.h"

namespace CC_Window_Tree_Interface
{
	extern std::string main_window_handle;
	extern std::map<std::string, Desktop_View*> view_tree;
	void initalize();
	void add_view(std::string handle, Desktop_View* view);

	void show_all();
	View* getWindow(View* hwnd);


}

#endif // !WINDOW_TREE