#include "interfaces.h"
#include "system_interface.h"

#ifdef IS_WIN32
#include "Windows/view/window.h"
#endif
Window* get_system_interface()
{
	#ifdef IS_WIN32
	return new Windows_Interface();
	#endif
	return NULL;
}
