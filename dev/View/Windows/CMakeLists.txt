set(PLATFORM_INCLUDE  "platform/framework.h"
                      "platform/Resource.h"
                      "platform/targetver.h"
    )


add_executable(WIN_VIEWS WIN32 main.cpp  ${PLATFORM_INCLUDE} "callbacks.h")