/*****************************************************************//**
 * \file   format.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW_FORMAT_INCLUDE_H
#define VIEW_FORMAT_INCLUDE_H

#include <thread>

#include "Interfaces/enums/view_type_enum.h"
#include "Interfaces/enums/display_type_enum.h"

#include "Messaging/consumers.h"
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
	 * \return Pointer to the newly created view
	 */
	virtual View* add_view(VIEW_TYPE_ENUM view);
	/**
	 * \brief Update all stale views.
	 *
	 * If a view is defined as stale, call on_refresh, on_paint, and on_display for the stale View.
	 * Stale is defined as different things for different devices. For System_View, it's that there's a new message on the System_Message stack.
	 * For a device, it's that the state has changed in some meaningful way.
	 */
	void update_views();

	/**
	 * \brief Get messages from the Int
	 */
	void process_internal_messages();

	/**
	 * \brief Destroy all views
	 *
	 * Call on_destroy on all views.
	 */
	void clean_views();

	/** An update step for the views */
	virtual void step() = 0;
protected:

	/** List of views that the format controls */
	std::vector<View*> view_list;
	/** Is the display loop running */
	bool format_running = false;
	/** Consume view messages */
	Message_Consumer* format_consumer = 0;
private:
};

#endif