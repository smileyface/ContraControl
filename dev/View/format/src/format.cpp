#include <map>

#include "../format.h"
#include "../View/view/view.h"
#include "../../factories/view_factory.h"

void Format::add_view(VIEW_TYPE_ENUM view)
{
}

void Format::initalize_format()
{
	format_consumer = new Message_Consumer(consumer_staleness, new View_Subsystem_Message());
}

void Format::update_views()
{
	for(auto i = view_list.begin(); i != view_list.end(); i++)
	{
		View* r = (*i);
		if(r->is_stale())
		{
			r->on_refresh();
			r->on_paint();
			r->on_display();
		}
	}
}

void Format::clean_views()
{
	for(auto i = view_list.begin(); i != view_list.end(); i++)
	{
		(*i)->on_destroy();
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