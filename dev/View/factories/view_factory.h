#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "Interfaces/enums/view_type_enum.h"
#include "Interfaces/enums/display_type_enum.h"

#include "../view/views.h"


View* view_factory(VIEW_TYPE_ENUM type, DISPLAY_TYPES display);

#endif
