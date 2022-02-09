#ifndef VIEW_FORMAT_INCLUDE_H
#define VIEW_FORMAT_INCLUDE_H

#include <string>
#include <thread>

#include "Interfaces/enums/view_type_enum.h"
#include "Interfaces/enums/display_type_enum.h"

#include "../view/view.h"

/**
 * \brief Format that the data will take.
 * 
 * Examples include: A console. A UI. WS2811 protocol. DMX protocol. Data pin. 
 * It contains a list of Views that feed it the data to "display." A Format mainly calls the handles for all it's known Views in every loop
 */
class Format
{
public:
	/**
	 * Initalize the Format. Generally includes an alive message and adding system messages.
	 */
	virtual void initalize() = 0;
	/**
	 * Add a new view to the format.
	 * \param view Type of view to add.
	 */
	virtual void add_view(VIEW_TYPE_ENUM view);
	/**
	 * \brief Update all stale views.
	 * 
	 * If a view is defined as stale, call on_refresh, on_paint, and on_display for the stale View.
	 * Stale is defined as different things for different devices. For System_View, it's that there's a new message on the System_Message stack. 
	 * For a device, it's that the state has changed in some meaningful way.
	 */
	void update_views();
	/**
	 * \brief Destroy all views
	 * 
	 * Call on_destroy on all views.
	 */
	void clean_views();

	/** Start the view in a new threaded loop. */
	void start_display();
	/** Stop the display loop */
	void stop_display();

protected:
	/** Loop to update the views */
	virtual void loop() = 0;
	/** List of views that the format controls */
	std::vector<View*> view_list;
	/** Is the display loop running */
	bool format_running = false;
	/** Thread that is handling the loop */
	std::thread* looping_thread  = nullptr;
private:
};

#endif