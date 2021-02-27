cmake_minimum_required(VERSION 3.6)

project(ContraControl VERSION 0.0.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(dev)


enable_testing()

add_subdirectory(unit_test)