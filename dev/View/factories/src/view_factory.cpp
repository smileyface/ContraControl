#include "..\view_factory.h"

#include "Utilities/exceptions.h"

View* view_factory(VIEW_TYPE_ENUM type, DISPLAY_TYPES display)
{
	switch (type)
	{
	case VIEW_TYPE_ENUM::SYSTEM:
		if (display == DISPLAY_TYPES::CONSOLE)
			return new Console_System_View();
		else
			throw UnimplementedFunctionException();
	default:
		throw UnimplementedFunctionException();
	}
}
