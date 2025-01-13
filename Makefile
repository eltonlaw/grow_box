.PHONY: all clean flash gdb libstm32g0 openocd

CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
GDB=arm-none-eabi-gdb
CFLAGS=-mcpu=cortex-m0plus -mthumb -g3 -O0
CFLAGS+=-I./STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
CFLAGS+=-I./STM32CubeG0/Drivers/CMSIS/Include
CFLAGS+=-I./STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Inc
CFLAGS+=-I./libstm32g0/include
CFLAGS+=-I./src
CFLAGS+=-I./include
CFLAGS+=-DSTM32G070xx
LDFLAGS=-Tlinker_script.ld -nostartfiles -nostdlib
LDFLAGS+=-L./libstm32g0 -lstm32g0
LDFLAGS+=-L. -lstm32g0xx_hal
LDFLAGS+=-lc -lm -lgcc
LDFLAGS+=-Wl,-Map main.map
OBJCOPY=arm-none-eabi-objcopy

HAL_SRC = $(wildcard STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/*.c)
EXCLUDE_FILES = \
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_timebase_rtc_alarm_template.c \
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_timebase_rtc_wakeup_template.c \
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_timebase_tim_template.c \
    STM32CubeG0/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_msp_template.c
HAL_SRC := $(filter-out $(EXCLUDE_FILES), $(HAL_SRC))
HAL_OBJ = $(HAL_SRC:.c=.o)
SRC = $(wildcard src/*.c)
ASM = $(wildcard src/*.s)

OBJ = $(SRC:.c=.o) $(ASM:.s=.o)

all: main.bin

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

main.elf: $(OBJ) libstm32g0.a libstm32g0xx_hal.a
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

libstm32g0.a:
	$(MAKE) -C $(basename $@) $@

libstm32g0xx_hal.a: $(HAL_OBJ)
	$(AR) rcs $@ $(HAL_OBJ)

clean-hal:
	rm -f $(HAL_OBJ)
	rm libstm32g0xx_hal.a

clean:
	rm -f *.elf *.bin
	$(MAKE) -C libstm32g0 clean

flash: main.bin
	STM32_Programmer_CLI -c port=SWD -w main.bin 0x8000000 -rst

openocd:
	openocd -f interface/stlink.cfg -f target/stm32g0x.cfg  -s ./openocd/tcl

gdb: main.elf
	$(GDB) $<

gdb-tui: main.elf
	$(GDB) --tui $<
