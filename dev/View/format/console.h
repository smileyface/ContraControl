#include "format.h"

class Console_Format : public Format
{
public:
	void initalize();
	void start_format();
	void add_view(std::string handle, View* view);

	bool is_running();
private:
	bool format_running = false;
	void console_display_thread();
};
