#include "../view_factory.h"

#include "Utilities/exceptions.h"
#include "Messaging/message_relay.h"

Device_View* view_factory(VIEW_TYPE_ENUM type, DISPLAY_TYPES display)
{
	Device_View* val = 0;
	switch (type)
	{
	case VIEW_TYPE_ENUM::LOG:
		switch(display)
		{
		case DISPLAY_TYPES::CONSOLE:
			val = new Console_Log_View();
			break;
		case DISPLAY_TYPES::FILE:
			val = new File_Log_View();
			break;
		}
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
		LOG_ERROR("Unimplemented Function", "View Factory");
	}
	return val;
}
