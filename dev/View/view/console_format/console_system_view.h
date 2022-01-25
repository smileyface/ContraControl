#ifndef CONSOLE_SYSTEM_VIEW_H
#define CONSOLE_SYSTEM_VIEW_H
#include <string>

#include "console_view.h"
#include "Messaging/consumers.h"

class Console_System_View : public Console_View
{
public:
    Console_System_View();

    virtual void on_display();

    void display_message();
    void set_system_id(std::string id);
private:
	std::string system_id;
    std::string message;
    std::string message_level;

    /**
    * .Message Consumer
    */
    Message_Consumer* message_consumer;
};

#endif