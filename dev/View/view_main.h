/*****************************************************************//**
 * \file   view_main.h
 * \brief  Main brains for the view. DO NOT INCLUDE. Include a viewCre_interface instead.
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW_EXECUTOR_H
#define VIEW_EXECUTOR_H
#include "format/format.h"
#include "Threading/threading.h"
#include "Messaging/message_relay.h"

/**
 * A unique identifier the handle a View
 */
typedef unsigned short View_Handle;

/**
 * An interface for every display.
 */
namespace view
{
	/**
	 * .The string of the namespace name. This is for locating Messages.
	 */
	static const char* subsystem_name = "View";
	/**
	 * Contained list of formats. Not for public consumption.
	 */
	extern std::map<View_Handle, Format*> list_of_formats;
	/**
	 * Boolean for the state of all views.
	 */
	extern bool view_running;
	/**
	 * Task to add view to the scheduler.
	 */
	extern Task view_task;

	/**
	 * Initalize all formats.
	 */
	void initalize();
	/**
	 * Start all Formats in threads.
	 */
	void start_view();
	/**
	 * Stop all Formats threads.
	 */
	void stop_view();
	/**
	 * Clean all the view.
	 */
	void clean_up();
	/**
	 * A single step of the view.
	 */
	void step();
	/**
	 * Add a new Format.
	 * \param display Type for Format to display.
	 * \return handle for Display
	 */
	View_Handle add_display(DISPLAY_TYPES display);

	/**
	 * Remove a Format
	 * \param handle Handle to specifiy the display to remove
	 */
	void remove_display(View_Handle handle);
}


#endif