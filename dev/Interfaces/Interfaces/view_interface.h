#ifndef MODEL_VIEW_INTERFACE
#define MODEL_VIEW_INTERFACE

/**
 * Interfaces to the View
 */
class View_Interfaces
{
public:
	class Main_Interface;
};

/**
 * Views interfaces to the Main thread.
 */
class View_Interfaces::Main_Interface
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


#endif