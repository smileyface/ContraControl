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
                    Interfaces/view_interface.h
                    Interfaces/main_interface.h
                    Interfaces/network_interface.h)
set(INTERFACE_SOURCE_FILES
                    Interfaces/src/controller_interface.cpp
                    Interfaces/src/model_interface.cpp
                    Interfaces/src/main_interface.cpp
                    Interfaces/src/view_interface.cpp)
set(INTERFACE_TYPE_HEADER_FILES
                    Interfaces/types/model_command.h
                    Interfaces/types/timed_command.h
                    Interfaces/types/device_label.h
                    Interfaces/types/state.h
                    Interfaces/types/channel.h
                    Interfaces/types/command_interface.h
                    Interfaces/types/view_capable.h
                    Interfaces/enums/display_type_enum.h
                    Interfaces/enums/view_type_enum.h)

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
target_link_libraries(System_Interface PUBLIC Controller Model)

set(INTERNAL_MESSAGE_TYPES_HEADER_FILES
                    Messaging/message_types/internal_message_type.h
                    Messaging/message_types/logging_message.h)
set(INTERNAL_MESSAGE_TYPES_SOURCE_FILES
                    Messaging/message_types/src/logging_message.cpp)
set(SYSTEM_MESSAGING_HEADER_FILES
                    ${INTERNAL_MESSAGE_TYPES_HEADER_FILES}
                    Messaging/consumers.h
                    Messaging/system_messaging.h)
set(SYSTEM_MESSAGING_SOURCE_FILES
                    ${INTERNAL_MESSAGE_TYPES_SOURCE_FILES}
                    Messaging/src/consumers.cpp
                    Messaging/src/system_messaging.cpp )

add_library(System_Messaging ${SYSTEM_MESSAGING_SOURCE_FILES} ${SYSTEM_MESSAGING_HEADER_FILES})
target_include_directories(System_Messaging
                            PUBLIC
                                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                                "$<INSTALL_INTERFACE:${CMAKE_BINARY_DIR}/inc/System_Messaging>")
# Set the output directory for build artifacts
  set_target_properties(System_Messaging
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Messaging"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Messaging"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

install(FILES ${INTERFACE_HEADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/inc/System_Interface)
install(FILES ${INTERFACE_TYPE_HEADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/inc/System_Interface/type)
install(FILES ${SYSTEM_MESSAGING_HEADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/inc/Messaging)