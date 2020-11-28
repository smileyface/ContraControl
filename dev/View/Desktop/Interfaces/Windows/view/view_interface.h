#ifndef VIEW_INTERFACE_PROC_H
#define VIEW_INTERFACE_PROC_H

#include "../../system_interface.h"
#ifdef IS_WIN32

#include <Windows.h>

extern HINSTANCE window_hInstance;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif // IS_WIN32

#endif // !VIEW_INTERFACE_PROC_H
