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
	View* new_view = Format::add_view(view);
	return new_view;
}

void Console_Format::step()
{
		process_internal_messages();
		update_views();
		//send off internal messages();
}