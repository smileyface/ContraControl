#include "../view_factory.h"

#include "Utilities/exceptions.h"

View* view_factory(VIEW_TYPE_ENUM type, DISPLAY_TYPES display)
{
	switch (type)
	{
	case VIEW_TYPE_ENUM::LOG:
		if (display == DISPLAY_TYPES::CONSOLE)
			return new Console_Log_View();
		else
			throw UnimplementedFunctionException();
	default:
		throw UnimplementedFunctionException();
	}
}
