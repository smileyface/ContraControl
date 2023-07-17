set(MODEL_DEVICES_HEADER_FILES 
                    devices/device.h
                    device.h )

set(MODEL_DEVICE_SOURCE_FILES
                    src/device.cpp "src/node.cpp")

set(MODEL_SYSTEM_HEADER_FILES
                    system/timer.h)

set(MODEL_NODE_HEADER_FILES
                    node/node.h)

set(MODEL_HEADER_FILES 
                    device.h)
                    

add_library(Model model_main.cpp ${MODEL_DEVICE_SOURCE_FILES} ${MODEL_DEVICES_HEADER_FILES} ${MODEL_SYSTEM_HEADER_FILES} ${MODEL_NODE_HEADER_FILES} ${MODEL_HEADER_FILES})
target_link_libraries(Model PUBLIC  System_Interface System_Messaging Utilities System_Threading)

set_property(TARGET Model PROPERTY CXX_STANDARD 11)