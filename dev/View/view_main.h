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

/**
 * An interface for every display.
 */
namespace view
{
	/**
	 * Contained list of formats. Not for public consumption.
	 */
	extern std::vector<Format*> list_of_formats;
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
	 * Add a new Format.
	 * \param display Type for Format to display.
	 * \return handle for Display
	 */
	int add_display(DISPLAY_TYPES display);
}


#endif