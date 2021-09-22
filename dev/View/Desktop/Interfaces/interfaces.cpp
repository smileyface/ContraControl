#include "interfaces.h"
#include "system_interface.h"

#ifdef _WIN32
#include "Windows/view/window.h"
#include "Windows/view/menu.h"
#endif
Window* get_system_interface()
{
	#ifdef _WIN32
	return new Windows_Interface();
	#endif
	return NULL;
}
Menu* get_menu(std::string txt)
{
	#ifdef _WIN32
	return new Windows_Menu(txt);
	#endif
	return NULL;
}
Menu_Item* get_menu(std::string txt, Menu_Item::Menu_Types flg, unsigned int id)
{
#ifdef _WIN32
	return new Menu_Item(txt, flg, id);
#endif
	return NULL;
}