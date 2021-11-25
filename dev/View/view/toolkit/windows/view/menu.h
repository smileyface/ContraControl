#ifndef WINDOWS_MENU_INTERFACE
#define WINDOWS_MENU_INTERFACE

#include "../../common/menu.h"

#include <windows.h>
class Windows_Menu : public Menu
{
public:
    Windows_Menu() 
    {
        text = "";
        flag = Menu_Item::Menu_Types::INVALID;
        this_menu = NULL;
    };
    Windows_Menu(std::string txt) 
    {
        text = txt;
        flag = Menu_Item::Menu_Types::MENU;
        this_menu = CreateMenu();
    };
    
    virtual void add_to_menu(Menu_Item* menu)
    {
        switch (menu->flag)
        {
        case Menu_Types::MENU_ITEM:
            AppendMenu(this_menu, menu_type_to_flag(menu->flag), menu->id, menu->text.c_str());
            break;
        case Menu_Types::MENU:
            HMENU win_menu = static_cast<Windows_Menu*>(menu)->get_menu();
            AppendMenu(this_menu, menu_type_to_flag(menu->flag), (UINT_PTR)win_menu, menu->text.c_str());
            break;
        }
        
    }

    HMENU get_menu()
    {
        return this_menu;
    }

private:
    long menu_type_to_flag(Menu_Types mt)
    {
        switch (mt)
        {
        case Menu_Types::MENU_ITEM:
            return MF_STRING;
            break;
        case Menu_Types::MENU:
            return MF_POPUP;
            break;

        }
    }
    HMENU this_menu;
};

#endif