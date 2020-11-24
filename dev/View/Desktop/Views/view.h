#ifndef WINDOW_MAIN_TYPE
#define WINDOW_MAIN_TYPE

#include "../Interfaces/interfaces.h"
#include "../../Common/view.h"
#include "../Interfaces/common/lib/dimensions.h"


constexpr auto IDM_QUIT = 101;

class Desktop_View : public View {
public:

    dimension dim = { DEFAULT_SIZE , DEFAULT_SIZE , DEFAULT_SIZE, DEFAULT_SIZE };

    void initalize(const std::string CLASS_NAME, const std::string WIN_TEXT) 
    {
        handle = get_system_interface();
        displayed = false;
        handle->set_window_name(CLASS_NAME);
        handle->set_window_text(WIN_TEXT);
        view_initalize();
    }


    virtual void on_destroy() = 0;
    virtual void on_paint() = 0;
    virtual void on_create() = 0;
    virtual void on_quit() = 0;
    virtual void on_mouse_down() = 0;
    virtual void on_command(unsigned int* command) = 0;

    virtual void create_menu(Menu& main_menu) = 0;;

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
    Window* handle;

    virtual void view_initalize() = 0;

};

#endif