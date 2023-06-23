#include "../view_factory.h"

#include "Utilities/exceptions.h"

View* view_factory(VIEW_TYPE_ENUM type, DISPLAY_TYPES display)
{
	View* val = 0;
	switch (type)
	{
	case VIEW_TYPE_ENUM::LOG:
		if (display == DISPLAY_TYPES::CONSOLE)
			val = new Console_Log_View();
		break;
	case VIEW_TYPE_ENUM::POPUP_OPTION:
		if(display == DISPLAY_TYPES::CONSOLE)
			val = new Console_Option_Popup();
		break;
	default:
		break;
	}
	if(val == 0)
	{
		throw UnimplementedFunctionException();
	}
	return val;
}
