cmake_minimum_required(VERSION 3.16)
project(grow_box_src C ASM)

include_directories(
    ${CMAKE_SOURCE_DIR}/STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ${CMAKE_SOURCE_DIR}/STM32CubeG0/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/libstm32g0/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

add_definitions(-DSTM32G070xx)

# Collect source files
file(GLOB SRC_FILES *.c)
file(GLOB ASM_FILES *.s)

add_executable(grow_box.elf ${SRC_FILES} ${ASM_FILES})
target_link_libraries(grow_box.elf stm32g0 stm32g0xx_hal)

add_custom_command(TARGET grow_box.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary grow_box.elf grow_box.bin
    COMMENT "Converting ELF to binary"
)
