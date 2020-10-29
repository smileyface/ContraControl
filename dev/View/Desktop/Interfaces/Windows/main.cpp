
#include <windows.h>
#include "../../desktop_main.h"
#include "view/view_interface.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    window_hInstance = hInstance;
    CC_Window_Tree_Interface::initalize();
    CC_Window_Tree_Interface::show_all();
    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

