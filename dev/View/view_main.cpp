#include "view_main.h"

#include "format/console.h"
#include "format/file.h"
#include "view/views.h"

std::map<View_Handle, Format*> view::list_of_formats = {};
bool view::view_running = false;
int display_id = 0;

Task view::view_task;

void view::initalize()
{
	view_task = Task("View", 2, .4);
	Scheduler::get_instance()->add_system_task(view::step);
	Scheduler::get_instance()->add_cleanup_task([] ()
												{});
	//initalize any format already added the system
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator).second->initalize();
	}
}

void view::start_view()
{
	LOG_INFO("View System added to the Scheduler", subsystem_name);
	Scheduler::get_instance()->add_task(&view::view_task);
	view_running = true;
}

void view::stop_view()
{
	LOG_INFO("View Stopped", subsystem_name);
	view_task.set_persistence(false);
	view_running = false;
}

void view::clean_up()
{
	for(auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator).second->clean_views();
	}
}

void  view::step()
{
	for(auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		view::view_task.add_subtask(Cleaned_Task([iterator] ()
									{
										(*iterator).second->step();
									}));
	}
}

View_Handle view::add_display(DISPLAY_TYPES display)
{
	int my_display_id = display_id;
	display_id++;
	switch (display)
	{
	case DISPLAY_TYPES::CONSOLE:
		list_of_formats[my_display_id] = new Console_Format();
		break;
	case DISPLAY_TYPES::FILE:
		list_of_formats[my_display_id] = new File_Format();
	}
	if(view_running)
	{
		list_of_formats[my_display_id]->initalize();
	}
	return my_display_id;
}

void view::remove_display(View_Handle handle)
{
	list_of_formats[handle]->clean_views();
	delete list_of_formats[handle];
	list_of_formats.erase(handle);
}
