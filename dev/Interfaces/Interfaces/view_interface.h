/*****************************************************************//**
 * \file   view_interface.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef MODEL_VIEW_INTERFACE
#define MODEL_VIEW_INTERFACE

 /**
  * Interfaces to the View
  */
class View_Interfaces
{
public:
	class Main_Interface;
	class Network_Interface;
};

/** Base that adds basic view interface functionality */

class View_Interface_Base
{
public:
	/**
	* 
	* This was never implemented. Will remain until these interfaces are replaced by internal messages
	* \param list_of_choices List to add to the popup.
	 * \return Option chosen
	 * 
	 */
	static int create_option_popup(std::vector<std::string> list_of_choices);
};

/**
 * Views interfaces to the Main thread.
 */
class View_Interfaces::Main_Interface : public View_Interface_Base
{
public:
	/**
	 * Start Views main execution loop.
	 */
	static void start_view();
	/**
	 * .Stop View main execution loop.
	 */
	static void stop_view();
	/**
	 * Add a display to the view.
	 * \param view_type The type of the display being added to View. It corresponds with DISPLAY_TYPES
	 */
	static void add_view(int view_type);
};

/**
 * Views interfaces to the Network subsystem.
 */
class View_Interfaces::Network_Interface : public View_Interface_Base
{
};

#endif