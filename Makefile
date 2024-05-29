.PHONY: all clean flash gdb libstm32g0 openocd

CC=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb
CFLAGS=-mcpu=cortex-m0plus -mthumb -g3 -O0
CFLAGS+=-I./STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
CFLAGS+=-I./STM32CubeG0/Drivers/CMSIS/Include
CFLAGS+=-I./libstm32g0/include
CFLAGS+=-I./src
CFLAGS+=-DSTM32G070xx
LDFLAGS=-Tlinker_script.ld -nostartfiles -nostdlib
LDFLAGS+=-L./libstm32g0 -lstm32g0
LDFLAGS+=-Wl,-Map main.map
OBJCOPY=arm-none-eabi-objcopy

SRC = $(wildcard src/*.c)

all: main.bin

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

main.elf: $(SRC) libstm32g0.a
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

libstm32g0.a:
	$(MAKE) -C $(basename $@) $@

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
