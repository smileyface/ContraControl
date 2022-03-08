set(NETWORK_INTERFACE_HEADERS
                    messages.h
                    system_interfaces/network_interface.h
                    system_interfaces/types/ipv4_addr.h
                    system_interfaces/types/network_status_state.h)
set(NETWORK_INTERFACE_SOURCE
                    src/connections.cpp
                    src/network_interface.cpp
                    src/windows_network_interface.cpp
                    src/linux_network_interface.cpp
                    src/ipv4_addr.cpp
                    src/network_status_state.cpp)
set(NETWORK_WINDOWS_INTERFACE_HEADERS
                    system_interfaces/windows_network_interface.h)
set(NETWORK_UNIX_INTERFACE_HEADERS
                    system_interfaces/unix_network_interface.h)
set(NETWORK_MESSAGE_HEADERS
                    messages/messaging.h
                    messages/node_communication.h)
set(NETWORK_MESSAGE_SOURCE
                    src/messaging.cpp
                    src/send_message.cpp)

add_library(Network ${NETWORK_INTERFACE_HEADERS} ${NETWORK_INTERFACE_SOURCE})
target_include_directories(Network 
                           PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/network)

target_link_libraries(Network System_Interface System_Messaging Utilities)
IF (CMAKE_HOST_WIN32)
    target_include_directories(Network
                                PRIVATE
                                ${NETWORK_WINDOWS_INTERFACE_HEADERS})
    target_link_libraries(Network wsock32 ws2_32)
    target_link_libraries(Network iphlpapi iphlpapi)

ELSEIF (CMAKE_HOST_UNIX)
    target_include_directories(Network
                                PRIVATE
                                ${NETWORK_UNIX_INTERFACE_HEADERS})
    target_link_libraries(Network pthread)
ENDIF()