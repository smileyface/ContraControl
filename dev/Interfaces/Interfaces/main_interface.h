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
	 * Let main start the controller.
	 */
	static void start_controller();
};

class Main_Interfaces::Model_Interface
{
public:
	/**
	 * .Let main initalize the model
	 */
	static void start_model();
};

/**
 * Main interfaces to the controller.
 */
class Main_Interfaces::View_Interface
{
public:
	static void start_view();
	static int add_display(DISPLAY_TYPES display);
	static void add_view(VIEW_TYPE_ENUM view);
	static void initalize(std::vector<DISPLAY_TYPES> types);

};
#endif // !MODEL_CONTROLLER_INTERFACE_H
