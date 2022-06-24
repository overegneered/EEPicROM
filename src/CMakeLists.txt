cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(EEPicROM C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(EEPicROM EEPicROM.c)
target_link_libraries(EEPicROM pico_stdlib)

pico_enable_stdio_usb(EEPicROM 1)
pico_enable_stdio_uart(EEPicROM 0)

pico_add_extra_outputs(EEPicROM)
