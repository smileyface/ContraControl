
set(UTILITIES_HEADER_FILES 
                    Logging/log_item.h
                    Logging/logging.h
                    save_reader.h
                    timer.h
                    utils.h
                    Logging/logging.cpp
    )

add_library(Utilities STATIC Logging/log_item.cpp  ${UTILITIES_HEADER_FILES})

install(TARGETS Utilities DESTINATION lib)
install(FILES ${UTILITIES_HEADER_FILES} DESTINATION include)