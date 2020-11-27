#ifndef WINDOW_MAIN_TYPE
#define WINDOW_MAIN_TYPE

#include "../Interfaces/interfaces.h"
#include "../../common/view.h"


constexpr auto IDM_QUIT = 101;

class Desktop_View : public View {
public:

    dimension dim = { DEFAULT_SIZE , DEFAULT_SIZE , DEFAULT_SIZE, DEFAULT_SIZE };

    Desktop_View() {
        handle = get_system_interface();
        displayed = false; 
    };
    virtual void initalize(const std::string CLASS_NAME, const std::string WIN_TEXT, int nCmdShow) = 0;
    virtual void on_destroy() = 0;
    virtual void on_paint() = 0;
    virtual void on_create() = 0;
    virtual void on_quit() = 0;
    virtual void on_mouse_down() = 0;
    virtual void on_command(unsigned int* command) = 0;

    virtual void create_menu(System_Interface::Menu& main_menu) = 0;;

    void display() {
        handle->show_window();
        displayed = true; 
    }
    void hide() {
        handle->hide_window();
        displayed = false;
    }

    bool operator==(const Desktop_View* h)
    {
        return &handle == &h->handle;
    }
protected:
    bool displayed;
    //window display handle
    System_Interface* handle;

};

#endif