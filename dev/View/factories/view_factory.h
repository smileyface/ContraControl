/*****************************************************************//**
 * \file   view_factory.h
 * \brief 
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "Interfaces/enums/view_type_enum.h"
#include "Interfaces/enums/display_type_enum.h"

#include "../view/views.h"

/**
 * Create a view from the display type and what it will display on.
 * \param type Type of View like Switch, or System_Message.
 * \param display What to display on like a console or WS2811 devices.
 * \return created View pointer.
 */
Device_View* view_factory(VIEW_TYPE_ENUM type, DISPLAY_TYPES display);

#endif
