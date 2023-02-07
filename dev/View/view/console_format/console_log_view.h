/*****************************************************************//**
 * \file   console_log_view.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef CONSOLE_LOG_VIEW_H
#define CONSOLE_LOG_VIEW_H

#include "console_view.h"
#include "../view_type/log_view_type.h"
#include "Messaging/consumers.h"

/** View for System_Messages on the Console */
class Console_Log_View : public Console_View, public Log_View_Type
{
public:
    Console_Log_View();
    virtual ~Console_Log_View();

    void on_display();
    void on_refresh();
    void on_paint();
    void on_exit();
    void on_destroy();

    bool is_stale();
private:
	std::string system_id;
    std::string message_;
    std::string message_level;

    std::string painted_message;
};

#endif