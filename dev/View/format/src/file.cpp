#include "../file.h"

#include "Messaging/message_relay.h"

void File_Format::initalize()
{
	format_consumer =
		Message_Relay::get_instance()->register_consumer<View_Subsystem_Message>();
	LOG_INFO("File Format On Line", "File Format");
}

Device_View* File_Format::add_view(VIEW_TYPE_ENUM view)
{
	Device_View* new_view = Format::create_view(view, DISPLAY_TYPES::FILE);
	return new_view;
}

void File_Format::step()
{
	process_internal_messages();
	update_views();
	//send off internal messages();
}
