#ifndef WINDOWS_VIEW_INTERFACE
#define WINDOWS_VIEW_INTERFACE

#include "../../system_interface.h"

#ifdef IS_WIN32
#include <Windows.h>
#endif // WIN32


class Windows_Interface : public System_Interface
{
public:
	void initalize(dimension dim);
	void show_window();
	void hide_window();
	void close_window();
	bool Windows_Interface::operator==(Windows_Interface h);

protected:
#ifdef IS_WIN32
	HWND handle;
#endif // WIN32

};

#endif