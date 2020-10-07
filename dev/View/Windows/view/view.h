#ifndef WINDOW_MAIN_TYPE
#define WINDOW_MAIN_TYPE



#include <windows.h>

extern HINSTANCE window_hInstance;

#define IDM_QUIT 101

struct dimension
{
    int x;
    int y;
    int height;
    int length;
};

class View {
public:

    dimension dim = { CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT, CW_USEDEFAULT };

    View() {
        displayed = false; 
        hwnd = NULL;
    };
    View(const wchar_t CLASS_NAME[], const wchar_t WIN_TEXT[], int nCmdShow);

    virtual void initalize(const char CLASS_NAME[], const char WIN_TEXT[], int nCmdShow);

    virtual void on_destroy() {};
    virtual void on_paint() {};
    virtual void on_create() {};
    virtual void on_quit() {};
    virtual void on_mouse_down() {};
    virtual void on_command(WPARAM command) {};

    virtual HMENU create_menu() {
        return NULL;
    };

    void display() {
        ShowWindow(hwnd, SW_SHOW);
        displayed = true; 
    }
    void hide() {
        ShowWindow(hwnd, SW_HIDE);
        displayed = false;
    }

    bool operator==(const HWND h)
    {
        return hwnd == h;
    }
protected:
    bool displayed;
    //window display handle
    HWND hwnd;

};

#endif