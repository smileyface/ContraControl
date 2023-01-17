/*****************************************************************//**
 * \file   view.h
 * \brief
 *
 * \author kason
 * \date   February 2022
 *********************************************************************/

#ifndef VIEW
#define VIEW

 /**
  * \brief way to view a Device.
  *
  * This parent class is meant to be extended to handle a viewing interface looking at a specific device, such as a system message, or a channel state.
  */
class View
{
public:
	/**
	 * Set up the data needed for this View.
	 */
	virtual void initalize()
	{ };
	/**
	 * Update the data for the view and set stale to false.
	 */
	virtual void on_refresh()
	{ };
	/**
	 * Display the painted frame on the screen.
	 */
	virtual void on_display()
	{ };
	/**
	* Called right before on_quit. Used to flatten any containers that is created with on_create.
   */
	virtual void on_destroy()
	{ };
	/**
	 * Called to create a frame to paint with on_display.
	 */
	virtual void on_paint()
	{ };
	/**
	 * Called when input recieved. Generally for handling the results of on_query().
	 */
	virtual void on_input()
	{ };
	/**
	 * Called when waiting on input from the user. Is a blocking call.
	 */
	virtual void on_query()
	{ };
	/**
	 * Create the View and any containers required. Called after initalized.
	 */
	virtual void on_create()
	{ };
	/**
	 * Clean up and exit the View.
	 */
	virtual void on_quit()
	{
		quit_the_view = true;
	};
	/**
	 * Send a direct command to the View. To be handled in a callback.
	 * \param command Command to be sent to the View.
	 */
	virtual void on_command(unsigned int command)
	{ };
	/**
	* Is the View out of touch with the model?
	* \return If the View is out of touch.
	*/
	virtual bool is_stale() = 0;

	/**
	 * Has the view been commanded to quit.
	 * \return If the view has been commanded to quit
	 */
	virtual bool quit()
	{
		return quit_the_view;
	};

	void exit()
	{
		quit_the_view = true;
	}

protected:
	/**
	 * State of the View's grasp on reality
	 */
	bool stale = true;
	/**
	 * Line up for destruction at the end of update.
	 */
	bool quit_the_view = false;
};

#endif
