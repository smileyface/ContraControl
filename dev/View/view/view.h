#ifndef VIEW
#define VIEW

class View
{
    bool stale = true;
    virtual void notify() = 0;
    virtual void notify_with_message(char* msg) = 0;

    virtual void initalize() = 0;
    virtual void on_display() = 0;
    virtual void on_destroy() = 0;
    virtual void on_paint() = 0;
    virtual void on_create() = 0;
    virtual void on_quit() = 0;
    virtual void on_command(unsigned int command) = 0;
};

struct RGB
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

#endif
