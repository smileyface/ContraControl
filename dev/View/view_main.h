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
#include "Utilities/subsystems.h"

/**
 * A unique identifier the handle a View
 */
typedef unsigned short View_Handle;

/**
 * An interface for every display.
 */
class View : public Subsystem
{
public:
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

	Format* get_format(View_Handle display_handle);

	/**
	 * Singleton get instance
	 * \return Singleton instance
	 */
	static View* get_instance();
	/**
	 * Singleton destroy instance
	 */
	static void destroy_instance();

	// Inherited via Subsystem	
	void start_loop() override;
	void stop_loop() override;
	bool is_running() override;
	char* subsystem_name() const override;
	void step() override;

private:
	View();
	~View();

	static View* instance;
	/**
	 * Contained list of formats. Not for public consumption.
	 */
	std::map<View_Handle, Format*> list_of_formats;
	/**
	 * Boolean for the state of all views.
	 */
	bool view_running;
	/**
	 * Task to add view to the scheduler.
	 */
	Task view_task;

	// Inherited via Subsystem

};

/**
 * Get the instance of the controller as an object. This is to convert a namespace to singleton.
 */
#define view View::get_instance()

#endif