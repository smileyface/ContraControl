#include <map>

#include "../format.h"
#include "../View/view/view.h"
#include "../../factories/view_factory.h"
#include "../Interfaces/Messaging/message_relay.h"
#include "../Utilities/Utilities/tools/classes.h"

Format::Format()
{ }

Format::~Format()
{ }

void Format::update_views()
{
	std::vector<std::vector<Device_View*>::iterator> destroy_list;
	for(auto i = view_list.begin(); i != view_list.end();)
	{
		Device_View* r = (*i);
		if(r->is_stale())
		{
			r->on_refresh();
			r->on_paint();
			r->on_display();
		}
		//Handle user queries in a series of blocking calls
		r->on_query();
		r->on_input();

		if(r->quit())
		{
			r->on_destroy();
			r->on_quit();
			delete (*i);
			i = view_list.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Format::clean_views()
{
	for(auto i = view_list.begin(); i != view_list.end(); i++)
	{
		(*i)->quit_view();
	}
	update_views();
	Message_Relay::get_instance()->deregister_consumer(format_consumer);
}

Device_View* Format::create_view(VIEW_TYPE_ENUM view, DISPLAY_TYPES type)
{
	LOG_INFO("Adding View: " + std::string(get_view_type_enum_as_string(view)), "Format");
	Device_View* new_view = view_factory(view, type);
	if(new_view != 0)
	{
		new_view->on_create();
		view_list.push_back(new_view);
	}
	return new_view;
}

void Format::process_internal_messages()
{
	std::vector<View_Subsystem_Message*> list_of_messages;
	for(Message_Ptr<Internal_Message> message = Message_Relay::get_instance()->pop(format_consumer); message != 0; message = Message_Relay::get_instance()->pop(format_consumer))
	{
		if(message.instance_of<Option_Popup_Message>())
		{
			Option_Popup_Message message_actualized = message.convert_type<Option_Popup_Message>();
			add_view(VIEW_TYPE_ENUM::POPUP_OPTION);
			std::string log_message = "Option Popup request recieved from subsystem ID " + std::to_string(static_cast<int>(message_actualized.get_sender()));
			LOG_INFO(log_message, "Option Popup Creation");
		}
	}
}