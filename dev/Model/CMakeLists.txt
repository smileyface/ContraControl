set(MODEL_DEVICES_HEADER_FILES 
                    devices/device.h
                    devices/gradient.h
                    devices/switch.h
                    devices/channel.h
                    devices/audio.h
                    device.h )

set(MODEL_SYSTEM_HEADER_FILES
                    system/timer.h)

set(MODEL_STATE_HEADER_FILES
                    state/state.h
                    state/rgb.h)

set(MODEL_NODE_HEADER_FILES
                    node/node.h)

set(MODEL_HEADER_FILES 
                    device.h)


add_library(Model model_main.cpp ${MODEL_DEVICES_HEADER_FILES} ${MODEL_SYSTEM_HEADER_FILES} ${MODEL_STATE_HEADER_FILES} ${MODEL_NODE_HEADER_FILES} ${MODEL_HEADER_FILES})
target_link_libraries(Model PUBLIC  System_Interface PUBLIC Utilities)
set_property(TARGET Model PROPERTY CXX_STANDARD 11)