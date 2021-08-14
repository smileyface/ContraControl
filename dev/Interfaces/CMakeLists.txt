###############################
#
#Interface CMake build file.
#
###############################

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()


if(NOT HOME)
  if(WIN32)
    string(REPLACE "\\" "/" HOME "$ENV{USERPROFILE}")
  else()
    set(HOME $ENV{HOME})
  endif()
endif()

set(INTERFACE_HEADER_FILES 
                    Interfaces/controller_interface.h
                    Interfaces/model_interface.h
                    Interfaces/view_interface.h)
set(INTERFACE_SOURCE_FILES 
                    Interfaces/controller_interface.cpp
                    Interfaces/model_interface.cpp)
set(INTERFACE_TYPE_HEADER_FILES
                    Interfaces/types/model_command.h 
                    Interfaces/types/timed_command.h 
                    Interfaces/types/device_label.h
                    Interfaces/types/state.h
                    Interfaces/types/channel.h
                    Interfaces/types/command_interface.h)

add_library(System_Interface ${INTERFACE_SOURCE_FILES} ${INTERFACE_HEADER_FILES})
target_include_directories(System_Interface 
                            PUBLIC
                                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"  
                                "$<INSTALL_INTERFACE:${CMAKE_BINARY_DIR}/inc/System_Interface>")
# Set the output directory for build artifacts
  set_target_properties(System_Interface
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Interfaces"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Interfaces"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


set(NETWORK_INTERFACE_HEADERS
                    Network/messages.h
                    Network/system_interfaces/network_interface.h)
set(NETWORK_INTERFACE_SOURCE
                    Network/src/connections.cpp
                    Network/src/network_interface.cpp
                    Network/src/windows_network_interface.cpp)
set(NETWORK_WINDOWS_INTERFACE_HEADERS
                    Network/system_interfaces/windows_network_interface.h)
set(NETWORK_UNIX_INTERFACE_HEADERS
                    Network/system_interfaces/unix_network_interface.h)
set(NETWORK_MESSAGE_HEADERS
                    Network/messages/messaging.h
                    Network/messages/node_communication.h)
set(NETWORK_MESSAGE_SOURCE
                    Network/src/messaging.cpp
                    Network/src/send_message.cpp)

add_library(Network ${NETWORK_INTERFACE_HEADERS} ${NETWORK_INTERFACE_SOURCE})
target_include_directories(Network 
                            PUBLIC
                                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"  
                                "$<INSTALL_INTERFACE:${CMAKE_BINARY_DIR}/inc/Network>"
                            PRIVATE ${NETWORK_MESSAGE_HEADERS})
target_sources(Network
               PRIVATE
                 ${NETWORK_MESSAGE_SOURCE})

# Set the output directory for build artifacts
  set_target_properties(Network
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Network"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Network"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

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
ENDIF()


install(FILES ${NETWORK_INTERFACE_HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/inc/Network)
install(FILES ${INTERFACE_HEADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/inc/System_Interface)
install(FILES ${INTERFACE_TYPE_HEADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/inc/System_Interface/type)