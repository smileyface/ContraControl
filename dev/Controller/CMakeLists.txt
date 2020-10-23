set(CONTROLLER_HEADER_FILES 
                    Commands/common/initalize.h
                    Commands/device/transitions/transition.h
                    Commands/device/transitions/linear_transition.h
                    Commands/device/off.h
                    Commands/device/on.h
                    Commands/command.h
                    commands.h
                    controller_main.h
                    types.h )

add_library(Controller controller_main.cpp ${CONTROLLER_HEADER_FILES})
