#ifndef CONSOLE_SYSTEM_VIEW_H
#define CONSOLE_SYSTEM_VIEW_H
#include <string>

#include "console_view.h"

class Console_System_View : public Console_View
{
public:
    Console_System_View()
    {
        system_id = "System";
    }
    virtual void notify();
    virtual void on_display();

    void display_message(std::string message);
    void set_system_id(std::string id);
private:
	std::string system_id;
    std::string message;
};

#endif