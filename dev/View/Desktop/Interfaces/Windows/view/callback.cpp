#include "view_interface.h"
#include "../../../desktop_main.h"
#include "../view/window.h"

/*
Support Function
*/
View* getViewFromMain(HWND hwnd)
{
    std::map<std::string, Desktop_View*>::iterator it;
    for (it = CC_Window_Tree_Interface::view_tree.begin(); it != CC_Window_Tree_Interface::view_tree.end(); it++)
    {
        Desktop_View* d_view = dynamic_cast<Desktop_View*>(it->second);
        Windows_Interface* windows_handle = dynamic_cast<Windows_Interface*>(d_view->get_handle());
        if (windows_handle->get_handle() == hwnd)
        {
            return it->second;
        }
    }

    throw "This window does not exist";
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            //CC_Window_Tree_Interface::getWindow(hwnd)->on_destroy();
            return 0;
        case WM_PAINT:
            //CC_Window_Tree_Interface::getWindow(hwnd)->on_paint();
            return 0;
        case WM_QUIT:
            //CC_Window_Tree_Interface::getWindow(hwnd)->on_quit();
            return 0;
        case WM_MBUTTONDOWN:
            //CC_Window_Tree_Interface::getWindow(hwnd)->on_mouse_down();
            return 0;
        case WM_COMMAND:
            View* raw_view = getViewFromMain(hwnd);
            Desktop_View* view = static_cast<Desktop_View*>(raw_view);
            view->on_command((unsigned int)wParam);
            return 0;
        }

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
