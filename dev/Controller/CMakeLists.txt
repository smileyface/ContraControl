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

set(CONTROLLER_SOURCE_FILES
                    commands/src/transition.cpp)

add_library(Controller controller_main.cpp ${CONTROLLER_HEADER_FILES} ${CONTROLLER_SOURCE_FILES})

target_include_directories(Controller 
                           PUBLIC 
                                ${CMAKE_CURRENT_SOURCE_DIR}/commands)
                            

target_link_libraries(Controller PUBLIC System_Interface)
target_link_libraries(Controller PUBLIC Utilities)
