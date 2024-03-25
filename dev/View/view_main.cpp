#include "view_main.h"

#include "format/console.h"
#include "format/file.h"
#include "view/views.h"

//FILE GLOBALS
int display_id = 0;

View* View::instance = 0;

View::View()
{
	view_task = Task("View", 2, .4);
	Scheduler::get_instance()->add_system_task(std::bind(&View::step, this));
	Scheduler::get_instance()->add_cleanup_task([] ()
												{});
	//initalize any format already added the system
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator).second->initalize();
	}
}

View::~View()
{
	for (auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		(*iterator).second->clean_views();
	}
	LOG_INFO("View Destroyed", "View");
}

View* View::get_instance()
{
	if (instance == 0)
	{
		instance = new View();
	}
	return instance;
}

void View::destroy_instance()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

void View::start_loop()
{
	LOG_INFO("View System added to the Scheduler", subsystem_name());
	Scheduler::get_instance()->add_task(&view_task);
	view_running = true;
}

void View::stop_loop()
{
	LOG_INFO("View Stopped", subsystem_name());
	view_task.set_persistence(false);
	view_running = false;
}

void  View::step()
{
	for(auto iterator = list_of_formats.begin(); iterator != list_of_formats.end(); iterator++)
	{
		view_task.add_subtask(Cleaned_Task([iterator] ()
									{
										(*iterator).second->step();
									}));
	}
}

View_Handle View::add_display(DISPLAY_TYPES display)
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

void View::remove_display(View_Handle handle)
{
	list_of_formats[handle]->clean_views();
	delete list_of_formats[handle];
	list_of_formats.erase(handle);
}

Format* View::get_format(View_Handle display_handle)
{
	Format* format = 0;
	if (list_of_formats.find(display_handle) != list_of_formats.end())
	{
		format = list_of_formats[display_handle];
	}
	return format;
}

bool View::is_running()
{
	return false;
}

char* View::subsystem_name() const
{
	return (char*)"View";
}
