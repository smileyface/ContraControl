#include <map>
#include <mutex>

#include "../format.h"
#include "../View/view/view.h"
#include "../../factories/view_factory.h"
#include "../Interfaces/Messaging/message_relay.h"
#include "../Utilities/Utilities/tools/classes.h"


std::mutex format_mutex;


View* Format::add_view(VIEW_TYPE_ENUM view)
{
	return 0;
}

void Format::update_views()
{
	auto i = view_list.begin();
	while( i != view_list.end())
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
			delete *i;
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
	format_mutex.lock();
	for(auto i = view_list.begin(); i != view_list.end(); i++)
	{
		(*i)->exit();
	}
}

void Format::process_internal_messages()
{
	std::vector<View_Subsystem_Message*> list_of_messages;
	View_Subsystem_Message* message = dynamic_cast<View_Subsystem_Message*>(Message_Relay::get_instance()->pop(format_consumer));
	for(; message != 0; message = dynamic_cast<Option_Popup_Message*>(Message_Relay::get_instance()->pop(format_consumer)))
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

	clean_views();
	while(view_list.size() > 0)
	{

	}

	format_running = false;
	if(looping_thread->joinable())
		looping_thread->join();
}

bool Format::running()
{
	return format_running && looping_thread->joinable();
}