set(DEVICE_TEST_FILES "tests/Devices/Switch.cpp"
                      "tests/Devices/Gradient.cpp"
                      "tests/Devices/RGB.cpp"
                      "tests/Devices/Invalid.cpp"
                      "tests/Devices/Node.cpp"
                      "tests/Network/Network.cpp"
                      "tests/Devices/Commands.cpp"
                      "tests/Subsystem.cpp"
                      "tests/Network/Network_Messages.cpp" 
                      "tests/Network/Errors.cpp" 
                      "tests/Network/Client.cpp" 
                      "tests/Errors/Exceptions.cpp"
                      "tests/Messaging/Internal_Messages.cpp"  
                      "tests/Messaging/Internal_Messages_Ptr.cpp"
                      "tests/View/Command_View_Message.cpp" 
                      "tests/View/File_View.cpp"
                      "tests/Keyboard/Action_Layer.cpp"
                      "tests/Keyboard/Action_Stack.cpp"
                      "tests/Keyboard/Keyboard_Buffer_Input.cpp" 
                      "tests/Keyboard/Keyboard_Hardware.cpp" 
                      "tests/Keyboard/Keyboard_System_Not_Connected.cpp" 
                      "tests/Scheduler/Task.cpp"
                      "tests/Scheduler/Scheduler.cpp" 
                      "tests/View/Console_View.cpp" 
                      "tests/View/View_Format.cpp")

add_library(Test_Utilities "test_utilities/pch.h"
                           "test_utilities/system_utilities.h"
                           "test_utilities/system_utilities.cpp"
                           "test_utilities/keyboard_interface_utilities.h" 
                           "test_utilities/keyboard_interface_utilities.cpp"
                           "test_utilities/keyboard_utility_object.cpp"
                           "test_utilities/linux_keyboard_utilities.cpp"
                           "test_utilities/win_keyboard_utilities.cpp"
                           "test_utilities/module_mains.h"
                           "test_utilities/test_utilities.h"
                           "test_utilities/test_utilities.cpp"
                           "test_utilities/device_utilities.h"
                           "test_utilities/device_utilities.cpp"
                           "test_utilities/node_utilities.h"
                           "test_utilities/node_utilities.cpp" )
target_link_libraries(Test_Utilities "gtest_main" Utilities Model Controller View_Library System_Interface Network System_Threading)



# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

add_executable(Static_Test ${DEVICE_TEST_FILES})
target_link_libraries(Static_Test gtest_main Test_Utilities)
#add_test(NAME Controller_Tests COMMAND Controller_Tests)
add_test(Devices Static_Test)

IF(CMAKE_COMPILER_IS_GNUCXX AND RUN_COVER)
  include(CodeCoverage.cmake)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/.cmake_modules")

  SET(CMAKE_CXX_FLAGS "-O1 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fprofile-arcs -ftest-coverage -fno-inline -fPIC")

  SETUP_TARGET_FOR_COVERAGE_COBERTURA(
        cov  # Name for custom target.
		    Static_Test         # Name of the test driver executable that runs the tests.
							    # NOTE! This should always have a ZERO as exit code
							    # otherwise the coverage generation will not complete.
		    coverage            # Name of output directory.
  )

ENDIF() # NOT CMAKE_COMPILER_IS_GNUCXX
