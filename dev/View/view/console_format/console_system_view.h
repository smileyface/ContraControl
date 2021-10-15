#ifndef CONSOLE_SYSTEM_VIEW_H
#define CONSOLE_SYSTEM_VIEW_H
#include "../view.h"

class Console_System_View : public Console_View
{
public:
    Console_System_View()
    {
        system_id = "System";
    }
    virtual void notify();
    virtual void initalize();
    virtual void on_refresh();
    virtual void on_display();
    virtual void on_destroy();
    virtual void on_paint();
    virtual void on_create();
    virtual void on_quit();
    virtual void on_command(unsigned int command);
    void display_message(std::string message);
private:
	std::string system_id;
    std::string message;
};

#endif