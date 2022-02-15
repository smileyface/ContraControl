/*****************************************************************//**
 * \file   main_interface.h
 * \brief
 *
 * \author kason
 * \date  February 2022
 *********************************************************************/

#ifndef MAIN_CONTROLLER_INTERFACE_H
#define MAIN_CONTROLLER_INTERFACE_H

#include <string>
#include <vector>

#include "enums/display_type_enum.h"
#include "enums/view_type_enum.h"
/**
 * Interfaces from main functions
 */
class Main_Interfaces
{
public:
	class Controller_Interface;
	class Model_Interface;
	class View_Interface;
};

/**
 * Main interfaces to the controller.
 */
class Main_Interfaces::Controller_Interface
{
public:
	/**
	 * Let main start the controller thread.
	 */
	static void start_controller();
	/** Let main stop and join the controller thread. */
	static void stop_controller();
};

/**
 * Main interfaces to the model.
 */
class Main_Interfaces::Model_Interface
{
public:
	/**
	 * Let main start the model thread.
	 */
	static void start_model();
	/** Let main stop and join the model thread. */
	static void stop_model();
};

/**
 * Main interfaces to the controller.
 */
class Main_Interfaces::View_Interface
{
public:
	/** Allow the Main thread to start the View Threads.*/
	static void start_view();
	/** Allow the Main thread to stop and join all the Format threads */
	static void stop_view();
	/**
	 * Add a view based on the DISPLAY_TYPES enum.
	 * \param view Type of view to add. Reference the DISPLAY_TYPES enum for which value to pass.
	 */
	static void add_view(int view);

};
#endif // !MODEL_CONTROLLER_INTERFACE_H
