#ifndef WINDOWS_VIEW_INTERFACE
#define WINDOWS_VIEW_INTERFACE

#include <unordered_map>
#include "../../common/window.h"
#include "menu.h"

#ifdef _WIN32
#include <Windows.h>
#endif // WIN32


class Windows_Interface : public Window
{
public:
	Windows_Interface() 
	{
		handle = NULL;
		main_menu = NULL;
		menu = new Windows_Menu();
	}
	virtual void initalize(Dimension dim);
	virtual void show_window();
	virtual void hide_window();
	virtual void close_window();
	virtual void set_menu(Menu* main);
	HWND get_handle();
	bool Windows_Interface::operator==(Windows_Interface h);

protected:
#ifdef _WIN32
	HWND handle;
	HMENU main_menu;
#endif // WIN32
};

#endif