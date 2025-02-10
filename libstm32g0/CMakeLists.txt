cmake_minimum_required(VERSION 3.16)
project(stm32g070rbt C)

include_directories(
    ../STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ../STM32CubeG0/Drivers/CMSIS/Include
    ../libstm32g0/include
)

add_definitions(-DSTM32G070xx)

# Collect source files
file(GLOB SRC_FILES src/*.c)

# Create static library
add_library(stm32g0 STATIC ${SRC_FILES})
