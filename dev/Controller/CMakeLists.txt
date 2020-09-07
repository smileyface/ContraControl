cmake_minimum_required(VERSION 3.10)


set(CONTROLLER_HEADER_FILES 
                    Commands/basic/initalize.h
                    Commands/basic/level.h
                    Commands/basic/off.h
                    Commands/basic/on.h
                    Commands/command.h
                    commands.h
                    controller_main.h
                    types.h
    )

add_library(Controller controller_main.cpp ${CONTROLLER_HEADER_FILES})
