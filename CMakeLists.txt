cmake_minimum_required(VERSION 3.6)

project(ContraControl VERSION 0.0.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RUN_COVER false CACHE BOOLEAN "Run code coverage")

if((DEFINED ENV{RUN_COVER} OR RUN_COVER) AND CMAKE_COMPILER_IS_GNUCXX)
    MESSAGE("Running Coverage")
	SET(CMAKE_CXX_FLAGS "-O1 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-arcs -ftest-coverage -fno-inline -fPIC")
endif()

add_subdirectory(dev)

enable_testing()

add_subdirectory(unit_test)