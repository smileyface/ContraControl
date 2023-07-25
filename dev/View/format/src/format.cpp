#include <map>

#include "../format.h"
#include "../View/view/view.h"
#include "../../factories/view_factory.h"
#include "../Interfaces/Messaging/message_relay.h"
#include "../Utilities/Utilities/tools/classes.h"

View* Format::add_view(VIEW_TYPE_ENUM view)
{
	std::string type(get_view_type_enum_as_string(view));
	LOG_INFO("Adding View: " + type, "Console Format");
	View* new_view = view_factory(view, DISPLAY_TYPES::CONSOLE);
	new_view->on_create();
	view_list.push_back(new_view);
	return new_view;
}

void Format::update_views()
{
	std::vector<std::vector<View*>::iterator> destroy_list;
	for(auto i = view_list.begin(); i != view_list.end(); i++)
	{
		View* r = (*i);
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
			destroy_list.push_back(i);
		}
	}
	for(int i = 0; i < destroy_list.size(); i++)
	{
		view_list.erase(destroy_list[i]);
	}
}

void Format::clean_views()
{
	for(auto i = view_list.begin(); i != view_list.end(); i++)
	{
		(*i)->quit_view();
	}
	Message_Relay::get_instance()->deregister_consumer(format_consumer);
}

void Format::process_internal_messages()
{
	std::vector<View_Subsystem_Message*> list_of_messages;
	for(Message_Ptr<Internal_Message> message = Message_Relay::get_instance()->pop(format_consumer); message != 0; message = Message_Relay::get_instance()->pop(format_consumer))
	{
		if(message.instance_of<Option_Popup_Message>())
		{
			Option_Popup_Message message_actualized = message.convert_type<Option_Popup_Message>();
			Console_Option_Popup* opm = dynamic_cast<Console_Option_Popup*>(add_view(VIEW_TYPE_ENUM::POPUP_OPTION));
			std::string log_message = "Option Popup request recieved from subsystem ID" + std::to_string(static_cast<int>(message_actualized.get_sender()));
			LOG_INFO(log_message, "Option Popup Creation");
		}
	}
}