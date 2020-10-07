set(PLATFORM_INCLUDE  "platform/framework.h"
                      "platform/Resource.h"
                      "platform/targetver.h"
    )

set(WINDOW_INCLUDE "view/view.h" 
                   "view/devices/led_view.h"
                   "window.h"  "view/devices/main_view.h" "views.h")
                       
add_executable(WIN_VIEWS WIN32 main.cpp  ${PLATFORM_INCLUDE} ${WINDOW_INCLUDE} "window.cpp" "view/view.cpp")