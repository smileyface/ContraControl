set(FORMAT_INCLUDES format/format.h
                    format/console.h
                    format/ui.h)

set(FORMAT_SOURCE format/src/format.cpp
                  format/src/console.cpp
                  format/src/ui.cpp)

set(CONSOLE_FORMAT_VIEWS_INCLUDES view/console_format/console_view.h
                                  view/console_format/console_log_view.h
                                  view/console_format/console_option_popup.h)

set(VIEW_INCLUDES view/view.h
                  view/views.h
                  ${CONSOLE_FORMAT_VIEWS_INCLUDES}
                  view/ui_format/ui_view.h
                  view/ui_format/ui_led_view.h
                  view/ui_format/ui_main_view.h "view/view_type/option_view_type.h")

set(VIEW_SOURCE view/src/ui_view.cpp
                view/src/log_view.cpp
                view/src/option_popup.cpp)

set(VIEW_FACTORIES_INCLUDES factories/view_factory.h)

set(VIEW_FACTORIES_SOURCE factories/src/view_factory.cpp)

set(VIEW_TOOLKIT_INCLUDES view/toolkit/dimensions.h
                          view/toolkit/interfaces.h
                          view/toolkit/menu.h
                          view/toolkit/painter.h
                          view/toolkit/window.h)

set(VIEW_TOOLKIT_SOURCE view/toolkit/src/interfaces.cpp)

add_library(View_Library view_main.cpp view_main.h ${FORMAT_INCLUDES} ${VIEW_INCLUDES} ${VIEW_FACTORIES_INCLUDES} ${VIEW_TOOLKIT_INCLUDES}  ${FORMAT_SOURCE} ${VIEW_SOURCE} ${VIEW_FACTORIES_SOURCE} ${VIEW_TOOLKIT_SOURCE} )

IF (CMAKE_HOST_WIN32)
    set(WIN32_INTERFACE_INCLUDES view/toolkit/windows/platform/framework.h
                                 view/toolkit/windows/platform/Resource.h
                                 view/toolkit/windows/platform/targetver.h)

    set(WIN32_TOOLKIT_INCLUDES view/toolkit/windows/view/menu.h
                               view/toolkit/windows/view/view_interface.h
                               view/toolkit/windows/view/window.h)

    target_include_directories(View_Library PRIVATE ${WIN32_INTERFACE_INCLUDES} ${WIN32_TOOLKIT_INCLUDES})

ENDIF()


target_link_libraries(View_Library PUBLIC  System_Interface System_Messaging Utilities)