#ifndef VIEW
#define VIEW

#include <vector>
#include <string>

/**
 * A way to view the model. This parent class is meant to be extended to handle a viewing interface, such as the console, a string of lights, or a windows UI. 
 */
class View
{
public:
    /**
     * Set up the data needed for this View.
     */
    virtual void initalize() {};
    /**
     * Update the data for the view and set stale to false.
     */
    virtual void on_refresh() {};
    /**
     * Display the painted frame on the screen.
     */
    virtual void on_display() {};
     /**
     * Called right before on_quit. Used to flatten any containers that is created with on_create.
    */
    virtual void on_destroy() {};
    /**
     * Called to create a frame to paint with on_display.
     */
    virtual void on_paint() {};
    /**
     * Create the View and any containers required. Called after initalized.
     */
    virtual void on_create() {};
    /**
     * Clean up and exit the View.
     */
    virtual void on_quit() {};
    /**
     * Send a direct command to the View. To be handled in a callback.
     */
    virtual void on_command(unsigned int command) {};
    /**
    * Is the View out of touch with the model?
    * \return If the View is out of touch.
    */
    bool is_stale() { return stale; }
protected:
    /**
     * State of the View's grasp on reality
     */
    bool stale = true;
};

struct RGB
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

typedef std::string View_Handle;

#endif
