#include <map>

#include "../format.h"
#include "../View/view/view.h"
#include "../../factories/view_factory.h"
#include "../Interfaces/Messaging/message_relay.h"
#include "../Utilities/Utilities/tools/classes.h"

View* Format::add_view(VIEW_TYPE_ENUM view)
{
	return 0;
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
			r->on_quit();
			r->on_destroy();
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
		(*i)->on_destroy();
	}
}

void Format::process_internal_messages()
{
	std::vector<View_Subsystem_Message*> list_of_messages;
	for(View_Subsystem_Message* message = dynamic_cast<View_Subsystem_Message*>(Message_Relay::get_instance()->front(format_consumer)); message != 0; message = dynamic_cast<Option_Popup_Message*>(Message_Relay::get_instance()->pop(format_consumer)))
	{
		if(instanceof<Option_Popup_Message>(message))
		{
			Console_Option_Popup* opm = dynamic_cast<Console_Option_Popup*>(add_view(VIEW_TYPE_ENUM::POPUP_OPTION));
			std::string log_message = "Option Popup request recieved from subsystem ID" + std::to_string(static_cast<int>(message->get_sender()));
			LOG_INFO(log_message, "Option Popup Creation");
		}
	}
}

void Format::start_display()
{
	format_running = true;
	looping_thread = new std::thread([this]
									 {
										 this->loop();
									 });
}

void Format::stop_display()
{
	format_running = false;
	looping_thread->join();
}