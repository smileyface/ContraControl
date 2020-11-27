#include "../../system_interface.h"
#ifdef IS_WIN32
#include <Windows.h>
#include "interfaces.h"
#include "../view/view_interface.h"
#include "..\..\interfaces.h"

const int DEFAULT_SIZE = CW_USEDEFAULT;
HINSTANCE window_hInstance;

void Windows_Interface::initalize(dimension dim)
{
    
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = window_hInstance;
    wc.lpszClassName = name.c_str();

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        name.c_str(),                     // Window class
        window_text.c_str(),                       // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        dim.x, dim.y, dim.length, dim.height,

        NULL,              // Parent window    
        NULL,     // Menu
        window_hInstance,  // Instance handle
        NULL               // Additional application data
    );

    if (hwnd == NULL)
    {
        throw "Window  not created";
    }
    handle = hwnd;
}

void Windows_Interface::show_window()
{
    ShowWindow(handle, SW_SHOW);
}

void Windows_Interface::hide_window()
{
    ShowWindow(handle, SW_HIDE);
}

void Windows_Interface::close_window()
{
    PostQuitMessage(0);
}

bool Windows_Interface::operator==(Windows_Interface h)
{
    return false;
}


void Windows_Interface::Painter::rectangle(dimension size, rgb color)
{

}

#endif // WIN32
