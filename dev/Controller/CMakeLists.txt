set(CONTROLLER_HEADER_FILES 
                    commands/device/device_command.h
                    commands/device/device_create.h
                    commands/device/off.h
                    commands/device/on.h
                    commands/device/assign.h
                    commands/device/device_initalize.h
                    commands/device/device_destruction.h
                    commands/command.h
                    commands.h
                    commander/commander.h
                    controller_main.h
                    system/timer.h
                    commands/node/node_command.h
                    commands/node/node_create.h
                    commands/node/node_destroy.h)

set(CONTROLLER_SOURCE_FILES
                    commands/src/assign.cpp
                    commands/src/command.cpp 
                    commands/src/device_create.cpp
                    commands/src/on.cpp
                    commands/src/off.cpp 
                    commands/src/device_command.cpp
                    commands/src/device_initalize.cpp
                    commands/src/device_destruction.cpp
                    commands/src/node_command.cpp
                    commands/src/node_create.cpp
                    commands/src/node_destroy.cpp
                    commander/src/commander.cpp)

add_library(Controller controller_main.cpp ${CONTROLLER_HEADER_FILES} ${CONTROLLER_SOURCE_FILES})

target_include_directories(Controller 
                           PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/commands)
                            

target_link_libraries(Controller PUBLIC System_Interface System_Messaging System_Threading Utilities)
