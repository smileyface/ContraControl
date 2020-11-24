#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

#include "menu.h"
#include "painter.h"

class Window
{
public:
    Window()
    {
        menu = new Menu();
        painter = new Painter();
    }
    void virtual initalize(dimension dim) = 0;
    void virtual show_window() = 0;
    void virtual hide_window() = 0;
    void virtual close_window() = 0;


    void set_window_name(std::string window_name)
    {
        name = window_name;
    }
    void set_window_text(std::string text)
    {
        window_text = text;
    }
    Menu* menu;
    Painter* painter;

protected:
    std::string name;
    std::string window_text;
};

#endif // !WINDOW_INTERFACE_H