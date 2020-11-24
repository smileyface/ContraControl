#ifndef WINDOWS_VIEW_INTERFACE
#define WINDOWS_VIEW_INTERFACE

#include <unordered_map>
#include "../../common/window.h"

#ifdef IS_WIN32
#include <Windows.h>
#endif // WIN32


class Windows_Interface : public Window
{
public:
	Windows_Interface() 
	{
		handle = NULL;
	}
	virtual void initalize(dimension dim);
	virtual void show_window();
	virtual void hide_window();
	virtual void close_window();
	bool Windows_Interface::operator==(Windows_Interface h);

protected:
#ifdef IS_WIN32
	HWND handle;
#endif // WIN32
};

#endif