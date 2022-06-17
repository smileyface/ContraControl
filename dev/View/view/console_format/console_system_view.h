/*****************************************************************//**
 * \file   console_system_view.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef CONSOLE_LOG_VIEW_H
#define CONSOLE_LOG_VIEW_H

#include "console_view.h"
#include "Messaging/consumers.h"

/** View for System_Messages on the Console */
class Console_Log_View : public Console_View
{
public:
    Console_Log_View();

    void on_display();
    void on_refresh();
    void on_paint();
private:
	std::string system_id;
    std::string message;
    std::string message_level;

    std::string painted_message;
    /**
    * .Message Consumer
    */
    Message_Consumer* message_consumer;
};

#endif