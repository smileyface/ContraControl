#ifndef VIEW_INTERFACE_PROC_H
#define VIEW_INTERFACE_PROC_H

#include "../../system_interface.h"
#ifdef WIN32

#include <Windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // WIN32

#endif // !VIEW_INTERFACE_PROC_H
