#include <iostream>
#include <thread>

#include "../console.h"
#include "../../view/view.h"
#include "../../factories/view_factory.h"
#include "Messaging/internal_messages.h"
#include "Messaging/message_relay.h"

void Console_Format::initalize()
{
	Format::initalize_format();
	LOG_INFO("Console On Line", "Console Format");
	add_view(VIEW_TYPE_ENUM::LOG);
}

void Console_Format::add_view(VIEW_TYPE_ENUM view)
{
	std::string type(get_view_type_enum_as_string(view));
	LOG_INFO("Adding View: " + type, "Console Format");
	view_list.push_back(view_factory(view, DISPLAY_TYPES::CONSOLE));
}

void Console_Format::loop()
{
	while(format_running)
	{
		update_views();
	}
}