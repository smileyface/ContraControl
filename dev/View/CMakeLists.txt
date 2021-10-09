set(FORMAT_INCLUDES "format/format.h"
                    "format/console.h"
                    "format/ui.h")

set(FORMAT_SOURCE "format/src/console.cpp"
                   "format/src/ui.cpp")

set(VIEW_INCLUDES "view/view.h"
                  "view/console_format/system_view.h"
                  "view/ui_format/led_view.h"
                  "view/ui_format/main_view.h")

set(VIEW_SOURCE "view/src/system_view.cpp")

set(VIEW_TOOLKIT_INCLUDES "view/toolkit/dimensions.h"
                          "view/toolkit/interfaces.h"
                          "view/toolkit/menu.h"
                          "view/toolkit/painter.h"
                          "view/toolkit/window.h")

set(VIEW_TOOLKIT_SOURCE "view/toolkit/src/interfaces.cpp")

IF (CMAKE_HOST_WIN32)
    set(WIN32_INTERFACE_INCLUDES "view/toolkit/windows/platform/framework.h"
                                 "view/toolkit/windows/platform/Resource.h"
                                 "view/toolkit/windows/platform/targetver.h")

    set(WIN32_TOOLKIT_INCLUDES "view/toolkit/windows/view/menu.h"
                               "view/toolkit/windows/view/view_interface.h"
                               "view/toolkit/windows/view/window.h")

                               
ENDIF()

                       
