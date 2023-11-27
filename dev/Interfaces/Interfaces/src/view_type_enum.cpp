#include "../enums/view_type_enum.h"

char* get_view_type_enum_as_string(VIEW_TYPE_ENUM view_type)
{
	char* val = 0;
	switch(view_type)
	{
	case VIEW_TYPE_ENUM::LOG:
		val = (char*) "Log";
	case VIEW_TYPE_ENUM::POPUP_OPTION:
		val = (char*) "Option Popup";
	}
	return val;
}
