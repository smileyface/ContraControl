
set(MODEL_DEVICES_HEADER_FILES 
                    devices/basic/device.h
                    devices/basic/gradient.h
                    devices/basic/switch.h
                    devices/single_complex/rgb.h
                    devices/single_complex/audio.h
                    device.h  "devices/single_complex/led.h")

set(MODEL_SYSTEM_HEADER_FILES
                    system/timer.h)

set(MODEL_STATE_HEADER_FILES
                    state/state.h)
set(MODEL_HEADER_FILES 
                    actions.h
                    device.h
                    types.h )


add_library(Model model_main.cpp ${MODEL_DEVICES_HEADER_FILES} ${MODEL_HEADER_FILES} ${MODEL_SYSTEM_HEADER_FILES})
target_link_libraries(Model Utilities Interface)
set_property(TARGET Model PROPERTY CXX_STANDARD 11)
