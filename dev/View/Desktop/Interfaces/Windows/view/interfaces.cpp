#include "../../system_interface.h"
#ifdef WIN32
#include <Windows.h>
#include "window.h"
#include "../view/view_interface.h"
#include "../../interfaces.h"

const int DEFAULT_SIZE = CW_USEDEFAULT;
HINSTANCE window_hInstance;

void Windows_Interface::initalize(Dimension dim)
{

    
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = window_hInstance;
    wc.lpszClassName = name.c_str();

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        name.c_str(),                   // Window class
        window_text.c_str(),            // Window text
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
    main_menu = CreateMenu();
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

void Windows_Interface::set_menu(Menu* main)
{
    main_menu = dynamic_cast<Windows_Menu*>(main)->get_menu();
    SetMenu(handle, main_menu);
}

HWND Windows_Interface::get_handle()
{
    return handle;
}

bool Windows_Interface::operator==(Windows_Interface h)
{
    return false;
}


#endif // WIN32
