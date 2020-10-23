#include "view.h"

class Main_View : public Desktop_View
{
public:
	Main_View() { };
	Main_View(const char CLASS_NAME[], const char WIN_TEXT[], int nCmdShow)
	{
		initalize(CLASS_NAME, WIN_TEXT, nCmdShow);
	}

	void initalize(const std::string CLASS_NAME, const std::string WIN_TEXT, int nCmdShow) {}

	void create_menu(System_Interface::Menu& main_menu)
	{
		handle->menu.add_menu_item(System_Interface::Menu_Item("Quit"));
		handle->menu.add_menu_item(System_Interface::Menu_Item("Add Device"));
	}

	void on_paint()
	{
		System_Interface::Painter paint;
		paint.rectangle({ 256, 256, 256, 256 }, { 255, 255, 255 });
	}

	void on_destroy()
	{
		handle->close_window();
	}

	void on_command(unsigned int* command)
	{
		if(*command == IDM_QUIT)
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

};