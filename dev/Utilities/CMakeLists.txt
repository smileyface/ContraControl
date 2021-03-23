
set(UTILITIES_HEADER_FILES 
                    "Logging/log_item.h"
                    "Logging/logging.h"
                    "save_reader.h"
                    "timer.h"
                    "utils.h"
                    "system.h"
                    "exceptions.h")

add_library(Utilities Logging/logging.cpp ${UTILITIES_HEADER_FILES})