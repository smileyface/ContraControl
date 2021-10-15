#ifndef MAIN_CONTROLLER_INTERFACE_H
#define MAIN_CONTROLLER_INTERFACE_H

#include <string>

#include "types/display_type_enum.h"
/**
 * Interfaces from main functions
 */
class Main_Interfaces
{
public:
	class Controller_Interface;
	class View_Interface;
};

/**
 * Main interfaces to the controller.
 */
class Main_Interfaces::Controller_Interface
{
public:
	/**
	 * Let main start the controller.
	 */
	static void start_controller();
};

/**
 * Main interfaces to the controller.
 */
class Main_Interfaces::View_Interface
{
public:
	static void start_view();
	static void add_display(DISPLAY_TYPES display);

};
#endif // !MODEL_CONTROLLER_INTERFACE_H
