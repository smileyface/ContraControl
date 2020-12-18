#include "view.h"
#include "../Interfaces/common/menu.h"

class Main_View : public Desktop_View
{
public:
	void create_menu()
	{
		Menu* file_menu = get_menu("File");
		file_menu->add_to_menu(get_menu("Quit", Menu_Item::Menu_Types::MENU_ITEM, IDM_QUIT));
		add_to_main_menu(file_menu);

		Menu* devices_menu = get_menu("Devices");
		Menu* add_devices_menu = get_menu("Add");
		add_devices_menu->add_to_menu(get_menu("LED", Menu_Item::Menu_Types::MENU_ITEM, 102));
		Menu* remove_devices_menu = get_menu("Remove");

		devices_menu->add_to_menu(add_devices_menu);
		devices_menu->add_to_menu(remove_devices_menu);
		add_to_main_menu(devices_menu);

	}

	void on_paint()
	{
		handle->painter->rectangle({ 256, 256, 256, 256 }, Model_RGB(255, 0, 255));
	}

	void on_destroy()
	{
		handle->close_window();
	}

	void on_command(unsigned int command)
	{
		if(command == IDM_QUIT)
		{
			on_quit();
		}
	}

	void on_quit()
	{
		on_destroy();
	}

	void on_mouse_down()
	{}

	void on_create() {}

protected:
	void view_initalize()
	{
		dim.x = 256;
		dim.y = 256;
		dim.height = 256;
		dim.length = 1024;
		handle->initalize(dim);
	}
};