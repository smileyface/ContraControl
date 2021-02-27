cmake_minimum_required(VERSION 3.6)

project(ContraControlDev VERSION 0.0.3)


#Add the controller
add_subdirectory(Interfaces)
add_subdirectory(Controller)
add_subdirectory(Model)
add_subdirectory(Utilities)
add_subdirectory(View)

