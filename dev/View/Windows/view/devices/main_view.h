#include "../view.h"

class Main_View : public View
{
public:
	Main_View() { View::View(); };
	Main_View(const char CLASS_NAME[], const char WIN_TEXT[], int nCmdShow)
	{
		initalize(CLASS_NAME, WIN_TEXT, nCmdShow);
		hwnd == View::hwnd;
	}

	HMENU create_menu()
	{
		HMENU main_menu = CreateMenu();
		HMENU file_menu = CreateMenu();
		AppendMenu(file_menu, MF_STRING, IDM_QUIT, "Quit");
		AppendMenu(main_menu, MF_POPUP, (UINT_PTR)file_menu, "File");


		HMENU add_device_menu = CreateMenu();

		AppendMenu(main_menu, MF_POPUP, (UINT_PTR)add_device_menu, "Add Device");

		return main_menu;
	}

	void on_paint()
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}

	void on_destroy()
	{
		PostQuitMessage(0);
	}

	void on_command(WPARAM command)
	{
		switch (LOWORD(command))
		{
		case IDM_QUIT:
			on_quit();
		}
	}

	void on_quit()
	{
		on_destroy();
	}

};