#include "view.h"
#include "../window.h"


HINSTANCE window_hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            CC_Window_Tree_Interface::getWindow(hwnd)->on_destroy();
            return 0;
        case WM_PAINT:
            CC_Window_Tree_Interface::getWindow(hwnd)->on_paint();
            return 0;
        case WM_QUIT:
            CC_Window_Tree_Interface::getWindow(hwnd)->on_quit();
            return 0;
        case WM_MBUTTONDOWN:
            CC_Window_Tree_Interface::getWindow(hwnd)->on_mouse_down();
            return 0;
        case WM_COMMAND:
            CC_Window_Tree_Interface::getWindow(hwnd)->on_command(wParam);
            return 0;
        }

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


View::View(const wchar_t CLASS_NAME[], const wchar_t WIN_TEXT[], int nCmdShow)
{
    
}

void View::initalize(const char CLASS_NAME[], const char WIN_TEXT[], int nCmdShow) {
    on_create();
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = window_hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        WIN_TEXT,                       // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        dim.x, dim.y, dim.length, dim.height,

        NULL,              // Parent window    
        create_menu(),     // Menu
        window_hInstance,  // Instance handle
        NULL               // Additional application data
    );

    if (hwnd == NULL)
    {
        throw "Window  not created";
    }

    displayed = false;
}

