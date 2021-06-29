IF (CMAKE_HOST_WIN32)
    file(WRITE "system.h" "#ifndef SYSTEM_VARIABLES\n #define SYSTEM_VARIABLES\n #define IS_WIN32\n#endif")
ENDIF()

set(COMMON_DESKTOP_VIEW_INCLUDE "Desktop/views.h"
                                "Desktop/Views/view.h" 
                                "Desktop/Views/led_view.h"
                                "Desktop/Views/main_view.h" 
                                "Desktop/Interfaces/interfaces.h"
                                "Desktop/desktop_main.h" 
                                "Desktop/Interfaces/system_interface.h")

set(COMMON_DESKTOP_INTERFACE_INCLUDE "Desktop/Interfaces/common/lib/dimensions.h")

set(COMMON_DESKTOP_VIEW_EXECUTABLES "Desktop/desktop_main.cpp" 
                                    "Desktop/Interfaces/interfaces.cpp")

IF (CMAKE_HOST_WIN32)

    set(WINDOWS_DESKTOP_VIEW_INCLUDES "Desktop/Interfaces/Windows/platform/framework.h"
                                      "Desktop/Interfaces/Windows/platform/Resource.h"
                                      "Desktop/Interfaces/Windows/platform/targetver.h"
                                      "Desktop/Interfaces/Windows/view/view_interface.h" 
                                      "Desktop/Interfaces/Windows/view/window.h" "Desktop/Interfaces/Windows/view/menu.h")


    set(WINDOWS_DESKTOP_VIEW_EXECUTABLES  "Desktop/Interfaces/Windows/view/interfaces.cpp" 
                                          "Desktop/Interfaces/Windows/view/callback.cpp"
                                          "Desktop/Interfaces/Windows/main.cpp")

    add_executable(WIN_VIEWS WIN32 ${WINDOWS_DESKTOP_VIEW_EXECUTABLES} ${COMMON_DESKTOP_VIEW_EXECUTABLES} ${WINDOWS_DESKTOP_VIEW_INCLUDES} ${COMMON_DESKTOP_VIEW_INCLUDE} "Desktop/Interfaces/Windows/view/menu.h")

    target_link_libraries(WIN_VIEWS PUBLIC System_Interface)
ENDIF()

                       
