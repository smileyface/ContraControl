#include "view.h"

class LED_View : public Desktop_View
{
    virtual void on_destroy()
    {};
    virtual void on_paint() {};
    virtual void on_create() {};
    virtual void on_quit() {};
    virtual void on_mouse_down() {};
    virtual void on_command(unsigned int command) {};
};