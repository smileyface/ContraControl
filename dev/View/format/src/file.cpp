#include "../file.h"

#include "Messaging/message_relay.h"

void File_Format::initalize()
{
	format_consumer =
		Message_Relay::get_instance()->register_consumer<View_Subsystem_Message>();
	LOG_INFO("File Format On Line", "File Format");
	add_view(VIEW_TYPE_ENUM::LOG);
}

View* File_Format::add_view(VIEW_TYPE_ENUM view)
{
	View* new_view = Format::create_view(view, DISPLAY_TYPES::FILE);
	return new_view;
}

void File_Format::step()
{ }
