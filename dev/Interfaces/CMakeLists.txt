set(INTERFACE_HEADER_FILES 
                    controller_interface.h
                    model_interface.h
                    view_interface.h 
                    common_objects.h)
set(INTERFACE_SOURCE_FILES 
                    controller_interface.cpp
                    model_interface.cpp
    )
set(INTERFACE_TYPE_HEADER_FILES
                    types/model_command.h 
                    types/timed_command.h "types/device_label.h")

set(NETWORK_INTERFACE_HEADERS
                    Network/connections.h)
set(NETWORK_INTERFACE_SOURCE
                    Network/connections.cpp)

add_library(Interface ${INTERFACE_SOURCE_FILES} ${INTERFACE_HEADER_FILES} ${INTERFACE_TYPE_HEADER_FILES})
add_library(Network ${NETWORK_INTERFACE_HEADERS} ${NETWORK_INTERFACE_SOURCE})