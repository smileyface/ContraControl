/*******************************************************************//**
 * \file   console_option_popup.h
 * \brief  
 * 
 * \author kason
 * \date   June 2022
 *********************************************************************/

#ifndef CONSOLE_OPTION_POPUP_VIEW
#define CONSOLE_OPTION_POPUP_VIEW

#include "console_view.h"

class Console_Option_Popup : public Console_View
{
public:
    void on_display();
    void on_refresh();
    void on_paint();
    void on_input();
    int get_option();

private:
    int option;
};
#endif

