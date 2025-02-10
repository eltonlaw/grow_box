set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
cmake_minimum_required(VERSION 3.16)
project(grow_box C ASM)

set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_AR /usr/bin/arm-none-eabi-ar)
set(CMAKE_OBJCOPY /usr/bin/arm-none-eabi-objcopy)
set(CMAKE_C_FLAGS "-mcpu=cortex-m0plus -mthumb -g3 -O0")
set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_SOURCE_DIR}/linker_script.ld -nostartfiles -nostdlib -lc -lm -lgcc -Wl,-Map=main.map")

include_directories(
    ./STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ./STM32CubeG0/Drivers/CMSIS/Include
    ./STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Inc
    ./libstm32g0/include
    ./src
    ./include
)

add_definitions(-DSTM32G070xx)
add_subdirectory(libstm32g0)
add_subdirectory(src)

file(GLOB HAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/*.c")
set(EXCLUDE_FILES
    "stm32g0xx_hal_timebase_rtc_alarm_template.c"
    "stm32g0xx_hal_timebase_rtc_wakeup_template.c"
    "stm32g0xx_hal_timebase_tim_template.c"
    "stm32g0xx_hal_msp_template.c"
)
# Filter out the excluded files
foreach(file ${EXCLUDE_FILES})
    list(FILTER HAL_SOURCES EXCLUDE REGEX "${file}$")
endforeach()
add_library(stm32g0xx_hal STATIC ${HAL_SOURCES})
target_include_directories(stm32g0xx_hal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

# Filter out the excluded files
foreach(file ${EXCLUDE_FILES})
    list(FILTER HAL_SOURCES EXCLUDE REGEX "${file}$")
endforeach()

# Flash target
add_custom_target(flash
    COMMAND STM32_Programmer_CLI -c port=SWD -w main.bin 0x8000000 -rst
    DEPENDS main.bin
    COMMENT "Flashing firmware"
)

# OpenOCD target
add_custom_target(openocd
    COMMAND openocd -f interface/stlink.cfg -f target/stm32g0x.cfg -s ./openocd/tcl
    COMMENT "Starting OpenOCD"
)

# GDB target
add_custom_target(gdb
    COMMAND arm-none-eabi-gdb main.elf
    DEPENDS main.elf
    COMMENT "Starting GDB session"
)

# GDB TUI target
add_custom_target(gdb-tui
    COMMAND arm-none-eabi-gdb --tui main.elf
    DEPENDS main.elf
    COMMENT "Starting GDB TUI session"
)
