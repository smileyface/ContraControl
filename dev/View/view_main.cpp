#include "view_main.h"

#include "format/console.h"
#include "view/views.h"

std::vector<Format*> view::list_of_formats = {};
bool view::view_running = false;
int display_id = 0;

Task view::view_task;

void view::initalize()
{
	view_task = Task("View", 2, .4);
	Scheduler::get_instance()->add_system_task(view::step);
	Scheduler::get_instance()->add_cleanup_task([] ()
												{ });
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator)->initalize();
	}
}

void view::start_view()
{
	LOG_INFO("View System added to the Scheduler", subsystem_name);
	Scheduler::get_instance()->add_task(&view::view_task);
}

void view::stop_view()
{
	LOG_INFO("View Stopped", subsystem_name);
	view_task.set_persistence(false);
	view_running = false;
}

void view::clean_up()
{
	for(int i = 0; i < list_of_formats.size(); i++)
	{
		list_of_formats[i]->clean_views();
	}
}

void  view::step()
{
	for(int i = 0; i < list_of_formats.size(); i++)
	{
		view::view_task.add_subtask(Cleaned_Task([i] ()
									{
										list_of_formats[i]->step();
									}));
	}
}

int view::add_display(DISPLAY_TYPES display)
{
	int my_display_id = display_id;
	display_id++;
	switch (display)
	{
	case DISPLAY_TYPES::CONSOLE:
		list_of_formats.emplace_back(new Console_Format());
		break;
	}
	return my_display_id;
}
