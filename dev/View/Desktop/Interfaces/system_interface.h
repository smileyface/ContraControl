#ifndef VIEW_SYSTEM_INTERFACES
#define VIEW_SYSTEM_INTERFACES

extern const int DEFAULT_SIZE;

#include "../../system.h"
#include <vector>
#include <string>

struct dimension
{
    int x;
    int y;
    int height;
    int length;
};

/*
*/
struct rgb
{
    int red;
    int green;
    int blue;
};


class System_Interface
{
public:
    struct Menu_Item
    {
        std::string text;

        Menu_Item() : text("") {}
        Menu_Item(std::string txt)
        {
            text = txt;
        }
    };
    class Menu
    {
    public:
        Menu(std::string name) {};
        Menu() {};
        const static std::string SEPERATOR() { return "~SEPERATOR~"; };
        virtual void add_menu_item(Menu_Item menu) {};
    };

    class Painter
    {
    public:
        void rectangle(dimension size, rgb color);
    };

    void virtual initalize(dimension dim) = 0;
    void virtual show_window() = 0;
    void virtual hide_window() = 0;
    void virtual close_window() = 0;

    Menu menu;

protected:
    std::string name;
    std::string window_text;
};

#endif