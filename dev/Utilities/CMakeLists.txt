
set(UTILITIES_HEADER_FILES 
                    Logging/log_item.h
                    Logging/logging.h
                    save_reader.h
                    timer.h
                    utils.h
    )

add_library(Utilities Logging/log_item.cpp Logging/logging.cpp ${UTILITIES_HEADER_FILES} "system.h")