cmake_minimum_required(VERSION 3.10)


set(INTERFACE_HEADER_FILES 
                    controller_interface.h
                    model_interface.h
    )
set(INTERFACE_SOURCE_FILES 
                    controller_interface.cpp
                    model_interface.cpp
    )

add_library(Interface ${INTERFACE_SOURCE_FILES} ${INTERFACE_HEADER_FILES})