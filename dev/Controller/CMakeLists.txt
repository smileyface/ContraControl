set(CONTROLLER_HEADER_FILES 
                    commands/common/initalize.h
                    commands/device/transitions/transition.h
                    commands/device/transitions/linear_transition.h
                    commands/device/off.h
                    commands/device/on.h
                    commands/command.h
                    commands.h
                    controller_main.h
                    system/timer.h)

add_library(Controller controller_main.cpp ${CONTROLLER_HEADER_FILES})

target_include_directories(Controller 
                           PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/commands)
                            

target_link_libraries(Controller PUBLIC System_Interface Utilities)