#ifndef CONSOLE_DISPLAY_VIEW_H
#define CONSOLE_DISPLAY_VIEW_H

#include "format.h"

class Console_Format : public Format
{
public:
	void initalize();
	DISPLAY_TYPES get_display_type() { return DISPLAY_TYPES::CONSOLE; };
	void add_view(VIEW_TYPE_ENUM view);

	bool is_running();
	void loop();


private:
	void console_display_thread();
};

#endif