cmake_minimum_required(VERSION 3.10)

set(MODEL_ACTIONS_HEADER_FILES 
                    devices/actions/device.h
                    devices/actions/gradient.h
                    devices/actions/switch.h
                    interfaces/model_actions.h
                    actions.h)

set(MODEL_DEVICES_HEADER_FILES 
                    devices/basic/device.h
                    devices/basic/gradient.h
                    devices/basic/switch.h
                    devices/single_complex/rgb.h
                    device.h)

set(MODEL_HEADER_FILES 
                    actions.h
                    device.h
                    types.h)

add_library(Model model_main.cpp ${MODEL_ACTIONS_HEADER_FILES} ${MODEL_DEVICES_HEADER_FILES} ${MODEL_HEADER_FILES})