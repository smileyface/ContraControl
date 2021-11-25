#ifndef VIEW
#define VIEW

#include <vector>
#include <string>

class View
{
public:
    virtual void notify() {};
    virtual void initalize() {};
    virtual void on_refresh() {};
    virtual void on_display() {};
    virtual void on_destroy() {};
    virtual void on_paint() {};
    virtual void on_create() {};
    virtual void on_quit() {};
    virtual void on_command(unsigned int command) {};
    bool is_stale() { return stale; }
protected:
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
