set(INTERFACE_HEADER_FILES 
                    controller_interface.h
                    model_interface.h
                    view_interface.h 
                    common_objects.h)
set(INTERFACE_SOURCE_FILES 
                    controller_interface.cpp
                    model_interface.cpp
    )

add_library(Interface ${INTERFACE_SOURCE_FILES} ${INTERFACE_HEADER_FILES} "Network/connection.h")