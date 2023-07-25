#include <iostream>
#include <thread>

#include "../console.h"
#include "../../view/view.h"
#include "../../factories/view_factory.h"
#include "Messaging/internal_messages.h"
#include "Messaging/message_relay.h"

void Console_Format::initalize()
{
	format_consumer =
		Message_Relay::get_instance()->register_consumer<View_Subsystem_Message>();
	LOG_INFO("Console On Line", "Console Format");
	add_view(VIEW_TYPE_ENUM::LOG);
}

View* Console_Format::add_view(VIEW_TYPE_ENUM view)
{
	std::string type(get_view_type_enum_as_string(view));
	LOG_INFO("Adding View: " + type, "Console Format");
	View* new_view = view_factory(view, DISPLAY_TYPES::CONSOLE);
	view_list.push_back(new_view);
	return new_view;
}

void Console_Format::step()
{
		process_internal_messages();
		update_views();
		//send off internal messages();
}