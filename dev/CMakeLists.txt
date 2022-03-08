cmake_minimum_required(VERSION 3.6)


project(ContraControlDev VERSION 0.0.5)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package (Threads)

add_subdirectory(Utilities)
add_subdirectory(Interfaces)
#Add the controller
add_subdirectory(Controller)
add_subdirectory(Model)
add_subdirectory(View)
add_subdirectory(Network)

add_subdirectory(Mains)