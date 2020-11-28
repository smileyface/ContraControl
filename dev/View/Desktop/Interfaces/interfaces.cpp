#include "interfaces.h"
#include "system_interface.h"

#ifdef IS_WIN32
#include "Windows/view/window.h"
#include "Windows/view/menu.h"
#endif
Window* get_system_interface()
{
	#ifdef IS_WIN32
	return new Windows_Interface();
	#endif
	return NULL;
}
Menu* get_menu(std::string txt)
{
	#ifdef IS_WIN32
	return new Windows_Menu(txt);
	#endif
	return NULL;
}
Menu_Item* get_menu(std::string txt, Menu_Item::Menu_Types flg, unsigned int id)
{
#ifdef IS_WIN32
	return new Menu_Item(txt, flg, id);
#endif
	return NULL;
}