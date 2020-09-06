cmake_minimum_required(VERSION 3.10)

project(Controller VERSION 0.0.3)

set(HEADER_FILES Commands/basic/initalize.h
                 Commands/basic/level.h
                 Commands/basic/off.h
                 Commands/basic/on.h
                 Commands/command.h)
target_include_directories(Controller PRIVATE Commands)

add_executable(Controller controller_main.cpp)
