if(NOT HOME)
  if(WIN32)
    string(REPLACE "\\" "/" HOME "$ENV{USERPROFILE}")
  else()
    set(HOME $ENV{HOME})
  endif()
endif()

set(UTILITIES_HEADER_FILES 
                    "Logging/log_item.h"
                    "Logging/logging.h"
                    "Utilities/save_reader.h"
                    "Utilities/timer.h"
                    "Utilities/utils.h"
                    "Utilities/exceptions.h" )
set(UTILITIES_SOURCE_FILES
                    "Logging/logging.cpp"
                    "Utilities/save_reader.cpp")

add_library(Utilities STATIC ${UTILITIES_SOURCE_FILES} ${UTILITIES_HEADER_FILES} )
target_include_directories(Utilities 
                            PUBLIC
                                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"  
                                "$<INSTALL_INTERFACE:${CMAKE_BINARY_DIR}/inc/Utilities>")
# Set the output directory for build artifacts
  set_target_properties(Utilities
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Utilities"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/Utilities"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

install(FILES ${UTILITIES_HEADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/inc/Utilities)