set(FORMAT_INCLUDES "format/format.h"
                    "format/console.h"
                    "format/ui.h")

set(FORMAT_SOURCE "format/src/console.cpp"
                   "format/src/ui.cpp")

set(VIEW_INCLUDES "view/view.h"
                  "view/ui_format/ui_view.h"
                  "view/ui_format/ui_led_view.h"
                  "view/ui_format/ui_main_view.h")

set(VIEW_SOURCE "view/src/ui_view.cpp")

set(VIEW_TOOLKIT_INCLUDES "view/toolkit/dimensions.h"
                          "view/toolkit/interfaces.h"
                          "view/toolkit/menu.h"
                          "view/toolkit/painter.h"
                          "view/toolkit/window.h")

set(VIEW_TOOLKIT_SOURCE "view/toolkit/src/interfaces.cpp")

add_library(View_Library view_main.cpp ${FORMAT_SOURCE} ${VIEW_SOURCE} ${VIEW_TOOLKIT_SOURCE} view_main.h ${FORMAT_INCLUDES} ${VIEW_INCLUDES} ${VIEW_TOOLKIT_INCLUDES}  "view/views.h")

IF (CMAKE_HOST_WIN32)
    set(WIN32_INTERFACE_INCLUDES "view/toolkit/windows/platform/framework.h"
                                 "view/toolkit/windows/platform/Resource.h"
                                 "view/toolkit/windows/platform/targetver.h")

    set(WIN32_TOOLKIT_INCLUDES "view/toolkit/windows/view/menu.h"
                               "view/toolkit/windows/view/view_interface.h"
                               "view/toolkit/windows/view/window.h")

                               
ENDIF()

                       
