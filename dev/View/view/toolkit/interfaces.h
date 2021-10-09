#ifndef VIEW_INTERFACES_H
#define VIEW_INTERFACES_H
#include "common/window.h"
#include "common/menu.h"
#include "common/painter.h"

Window* get_system_interface();
Menu* get_menu(std::string txt);
Menu_Item* get_menu(std::string txt, Menu_Item::Menu_Types flg, unsigned int id);

#endif